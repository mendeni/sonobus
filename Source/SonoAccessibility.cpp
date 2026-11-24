// SPDX-License-Identifier: GPLv3-or-later WITH Appstore-exception
// Screen reader (JAWS / NVDA / VoiceOver) helpers for SonoBus.

#include "SonoAccessibility.h"

namespace SonoAccessibility
{

//==============================================================================
void scrollIntoView (Component* comp)
{
    if (comp == nullptr)
        return;

    for (auto* viewport = comp->findParentComponentOfClass<Viewport>();
         viewport != nullptr;
         viewport = viewport->findParentComponentOfClass<Viewport>())
    {
        auto* viewed = viewport->getViewedComponent();

        if (viewed == nullptr || ! (viewed == comp || viewed->isParentOf (comp)))
            continue;

        const auto target = viewed->getLocalArea (comp, comp->getLocalBounds());
        const auto view   = viewport->getViewArea();

        auto x = view.getX();
        auto y = view.getY();

        if (target.getRight() > view.getRight())    x = target.getRight() - view.getWidth();
        if (target.getX() < x)                      x = target.getX();
        if (target.getBottom() > view.getBottom())  y = target.getBottom() - view.getHeight();
        if (target.getY() < y)                      y = target.getY();

        if (x != view.getX() || y != view.getY())
            viewport->setViewPosition (x, y);
    }
}

//==============================================================================
Component* ScrollingKeyboardFocusTraverser::getNextComponent (Component* current)
{
    auto* next = KeyboardFocusTraverser::getNextComponent (current);
    scrollIntoView (next);
    return next;
}

Component* ScrollingKeyboardFocusTraverser::getPreviousComponent (Component* current)
{
    auto* prev = KeyboardFocusTraverser::getPreviousComponent (current);
    scrollIntoView (prev);
    return prev;
}

Component* ScrollingKeyboardFocusTraverser::getDefaultComponent (Component* parentComponent)
{
    auto* comp = KeyboardFocusTraverser::getDefaultComponent (parentComponent);
    scrollIntoView (comp);
    return comp;
}

//==============================================================================
namespace
{
    struct FocusScroller : public FocusChangeListener,
                           public DeletedAtShutdown
    {
        FocusScroller()             { Desktop::getInstance().addFocusChangeListener (this); }
        ~FocusScroller() override   { Desktop::getInstance().removeFocusChangeListener (this); clearSingletonInstance(); }

        void globalFocusChanged (Component* focused) override
        {
            scrollIntoView (focused);
        }

        JUCE_DECLARE_SINGLETON_INLINE (FocusScroller, false)
    };

    String spokenNameOf (Component* c)
    {
        if (c == nullptr)
            return {};

        if (c->getTitle().isNotEmpty())
            return c->getTitle();

        if (auto* b = dynamic_cast<Button*> (c))
            return b->getButtonText();

        return {};
    }

    template <typename Fn>
    void forEachDescendant (Component& parent, Fn&& fn)
    {
        for (auto* child : parent.getChildren())
        {
            fn (child);

            // Don't dig into the internals of compound widgets
            if (dynamic_cast<ComboBox*> (child) == nullptr && dynamic_cast<ListBox*> (child) == nullptr)
                forEachDescendant (*child, fn);
        }
    }

    Component* findFocusableByName (Component& parent, const String& name)
    {
        Component* found = nullptr;

        forEachDescendant (parent, [&] (Component* c)
        {
            if (found == nullptr && c->isShowing() && c->getWantsKeyboardFocus() && spokenNameOf (c) == name)
                found = c;
        });

        return found;
    }

    String nameFromLabelText (const String& labelText)
    {
        auto name = labelText.trim();

        // Give the bare "Output:" / "Input:" / "Device:" labels a clearer spoken name
        if (name == TRANS ("Output:"))  return TRANS ("Output device");
        if (name == TRANS ("Input:"))   return TRANS ("Input device");
        if (name == TRANS ("Device:"))  return TRANS ("Audio device");

        if (name.endsWithChar (':'))
            name = name.dropLastCharacters (1).trimEnd();

        return name;
    }

    struct FocusReturner : public ComponentListener
    {
        FocusReturner (Component& popup, Component& returnTo) : target (&returnTo)
        {
            popup.addComponentListener (this);
        }

        void componentBeingDeleted (Component& popup) override
        {
            popup.removeComponentListener (this);

            MessageManager::callAsync ([t = target]
            {
                if (t == nullptr || ! t->isShowing())
                    return;

                auto* focused = Component::getCurrentlyFocusedComponent();

                if (focused == nullptr || ! focused->isShowing() || focused->isParentOf (t))
                {
                    scrollIntoView (t.getComponent());
                    t->grabKeyboardFocus();
                }
            });

            delete this;
        }

        Component::SafePointer<Component> target;
    };
}

void installFocusScroller()
{
    FocusScroller::getInstance();
}

// Spoken announcements were switched off in SonoBus in 2021 (commit 682ed6e0, "reverted
// accessibility announcements because of issues") with the much older JUCE 6.1 of the time.
// They are all routed through here now, so if they misbehave they can be turned off in one place.
static constexpr bool announcementsEnabled = true;

void announce (const String& message, AccessibilityHandler::AnnouncementPriority priority)
{
    if (announcementsEnabled && message.isNotEmpty())
        AccessibilityHandler::postAnnouncement (message, priority);
}

void returnFocusWhenClosed (Component& popup, Component& returnTo)
{
    new FocusReturner (popup, returnTo); // deletes itself when popup is deleted
}

//==============================================================================
AudioDeviceSelectorHelper::AudioDeviceSelectorHelper (AudioDeviceSelectorComponent& sel, AudioDeviceManager& dm)
    : selector (&sel), manager (dm)
{
    manager.addChangeListener (this);
    Desktop::getInstance().addFocusChangeListener (this);
    sel.addComponentListener (this);
    refresh();
}

AudioDeviceSelectorHelper::~AudioDeviceSelectorHelper()
{
    manager.removeChangeListener (this);
    Desktop::getInstance().removeFocusChangeListener (this);

    if (selector != nullptr)
    {
        selector->removeComponentListener (this);

        forEachDescendant (*selector, [this] (Component* c)
        {
            if (c->getProperties().contains ("sonoA11yKeys"))
            {
                c->removeKeyListener (this);
                c->getProperties().remove ("sonoA11yKeys");
            }
        });
    }
}

void AudioDeviceSelectorHelper::refresh()
{
    if (selector == nullptr || refreshing)
        return;

    const ScopedValueSetter<bool> svs (refreshing, true);

    std::vector<ListBox*> channelLists;
    std::vector<Button*> selectAllButtons;

    forEachDescendant (*selector, [&] (Component* c)
    {
        if (auto* label = dynamic_cast<Label*> (c))
        {
            if (auto* owner = label->getAttachedComponent())
            {
                const auto name = nameFromLabelText (label->getText());

                if (name.isNotEmpty() && owner->getTitle() != name)
                    owner->setTitle (name);

                // The control now carries this text as its own name
                label->setAccessible (false);

                if (auto* list = dynamic_cast<ListBox*> (owner))
                    channelLists.push_back (list);
            }
        }
        else if (auto* button = dynamic_cast<Button*> (c))
        {
            if (button->getButtonText() == TRANS ("Select All"))
                selectAllButtons.push_back (button);

            // Make the tooltip (e.g. "Plays a test tone") available as the spoken description
            if (button->getDescription().isEmpty() && button->getTooltip().isNotEmpty())
                button->setDescription (button->getTooltip());
        }
    });

    // Space / Enter toggles a channel and speaks the result
    for (auto* list : channelLists)
    {
        if (! list->getProperties().contains ("sonoA11yKeys"))
        {
            list->addKeyListener (this);
            list->getProperties().set ("sonoA11yKeys", true);
        }
    }

    // Two buttons are both called "Select All"; say which channel list each one is for
    for (auto* button : selectAllButtons)
    {
        const auto bb = selector->getLocalArea (button->getParentComponent(), button->getBounds());
        ListBox* best = nullptr;
        int bestDistance = std::numeric_limits<int>::max();

        for (auto* list : channelLists)
        {
            const auto lb = selector->getLocalArea (list->getParentComponent(), list->getBounds());
            const auto distance = std::abs (lb.getCentreY() - bb.getCentreY());

            if (distance < bestDistance)
            {
                bestDistance = distance;
                best = list;
            }
        }

        if (best != nullptr && best->getTitle().isNotEmpty())
        {
            const auto name = button->getButtonText() + ": " + best->getTitle();

            if (button->getTitle() != name)
                button->setTitle (name);
        }
    }
}

void AudioDeviceSelectorHelper::changeListenerCallback (ChangeBroadcaster*)
{
    // The selector rebuilds its own controls in response to this same message,
    // so wait until it has finished before naming controls and restoring focus.
    MessageManager::callAsync ([weakThis = WeakReference<AudioDeviceSelectorHelper> (this)]
    {
        if (weakThis != nullptr)
            weakThis->afterDeviceChange();
    });
}

void AudioDeviceSelectorHelper::afterDeviceChange()
{
    refresh();
    restoreFocusIfLost();
}

void AudioDeviceSelectorHelper::restoreFocusIfLost()
{
    if (selector == nullptr || ! selector->isShowing())
        return;

    // Still alive and focused? Nothing to do.
    if (lastFocused != nullptr || lastFocusedName.isEmpty())
        return;

    auto* focused = Component::getCurrentlyFocusedComponent();

    const bool focusWasLost = focused == nullptr
                               || ! focused->isShowing()
                               || focused == selector.getComponent()
                               || focused->isParentOf (selector.getComponent());

    if (! focusWasLost)
        return;

    if (auto* replacement = findFocusableByName (*selector, lastFocusedName))
    {
        scrollIntoView (replacement);
        replacement->grabKeyboardFocus();
    }
}

void AudioDeviceSelectorHelper::globalFocusChanged (Component* focused)
{
    if (focused != nullptr && selector != nullptr && selector->isParentOf (focused))
    {
        lastFocused = focused;
        lastFocusedName = spokenNameOf (focused);

        // A row inside a list: remember the list itself
        if (lastFocusedName.isEmpty())
            if (auto* list = focused->findParentComponentOfClass<ListBox>())
            {
                lastFocused = list;
                lastFocusedName = spokenNameOf (list);
            }
    }
}

void AudioDeviceSelectorHelper::componentMovedOrResized (Component&, bool, bool wasResized)
{
    if (wasResized)
        refresh();
}

void AudioDeviceSelectorHelper::componentVisibilityChanged (Component&)
{
    refresh();
}

bool AudioDeviceSelectorHelper::keyPressed (const KeyPress& key, Component* origin)
{
    auto* list = dynamic_cast<ListBox*> (origin);

    if (list == nullptr || key.getModifiers().isAnyModifierKeyDown())
        return false;

    if (! (key.isKeyCode (KeyPress::spaceKey) || key.isKeyCode (KeyPress::returnKey)))
        return false;

    auto* model = list->getListBoxModel();

    if (model == nullptr || model->getNumRows() <= 0)
        return false;

    auto row = list->getSelectedRow();

    if (row < 0)
    {
        row = 0;
        list->selectRow (row);
    }

    model->returnKeyPressed (row); // turns the channel on or off

    // The row name ends with ", selected" when the channel is on
    const auto suffix = ", " + TRANS ("selected");
    auto name = model->getNameForRow (row);
    const bool isOn = name.endsWith (suffix);

    if (isOn)
        name = name.dropLastCharacters (suffix.length());

    list->repaintRow (row);
    announce (name + ", " + (isOn ? TRANS ("checked") : TRANS ("not checked")),
              AccessibilityHandler::AnnouncementPriority::high);

    return true;
}

} // namespace SonoAccessibility
