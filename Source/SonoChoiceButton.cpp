// SPDX-License-Identifier: GPLv3-or-later WITH Appstore-exception
// Copyright (C) 2020 Jesse Chappell


#include "SonoChoiceButton.h"

SonoChoiceButton::SonoChoiceButton()
{
    textLabel = std::make_unique<Label>();
    addAndMakeVisible(textLabel.get());
    textLabel->setJustificationType(Justification::centredLeft);
    textLabel->setAccessible(false);

    selIndex = 0;
    addListener(this);
    
}

SonoChoiceButton::~SonoChoiceButton()
{
    
}

void SonoChoiceButton::clearItems()
{
    items.clear();
    idList.clear();
    textLabel->setText("", dontSendNotification);
}

void SonoChoiceButton::addItem(const String & name, int ident, bool separator, bool disabled)
{
    items.add(GenericItemChooserItem(name, Image(), nullptr, separator, disabled));
    idList.add(ident);
}

void SonoChoiceButton::addItem(const String & name, int ident, const Image & newItemImage, bool separator, bool disabled)
{
    items.add(GenericItemChooserItem(name, newItemImage, nullptr, separator, disabled));
    idList.add(ident);
}


void SonoChoiceButton::setSelectedItemIndex(int index, NotificationType notification)
{
    selIndex = index;
    if (selIndex < items.size()) {
        textLabel->setText(items[selIndex].name, dontSendNotification);
    }

    if (notification != dontSendNotification) {
        int ident = index < idList.size() ? idList[index] : 0;
        listeners.call (&SonoChoiceButton::Listener::choiceButtonSelected, this, index, ident);
    }

    if (auto* handler = getAccessibilityHandler()) {
        handler->notifyAccessibilityEvent (AccessibilityEvent::valueChanged);
    }

    repaint();
}

bool SonoChoiceButton::selectAdjacentItem(int delta)
{
    // skip disabled entries (e.g. explanatory notes in the list)
    for (int i = selIndex + delta; i >= 0 && i < items.size(); i += delta) {
        if (!items[i].disabled) {
            setSelectedItemIndex(i, sendNotificationSync);
            return true;
        }
    }
    return true; // at the end of the list: consume the key so focus doesn't jump
}

bool SonoChoiceButton::keyPressed (const KeyPress& key)
{
    if (!items.isEmpty()) {
        const auto mods = key.getModifiers();

        if ((key.isKeyCode(KeyPress::downKey) && mods.isAltDown()) || key.isKeyCode(KeyPress::F4Key)) {
            showPopup();
            return true;
        }

        if (arrowKeysChangeSelection && !mods.isAnyModifierKeyDown()) {
            if (key.isKeyCode(KeyPress::upKey) || key.isKeyCode(KeyPress::leftKey))
                return selectAdjacentItem(-1);
            if (key.isKeyCode(KeyPress::downKey) || key.isKeyCode(KeyPress::rightKey))
                return selectAdjacentItem(1);
        }
    }

    return SonoTextButton::keyPressed(key);
}

void SonoChoiceButton::setSelectedId(int ident, NotificationType notification)
{
    for (int i=0; i < idList.size(); ++i) {
        if (idList[i] == ident) {
            setSelectedItemIndex(i, notification);
            break;
        }
    }
}


String SonoChoiceButton::getItemText(int index) const
{
    if (isPositiveAndBelow(index, items.size())) {
        return items[index].name;
    }
    
    return "";
}

String SonoChoiceButton::getCurrentText() const
{
    return textLabel->getText();
}


void SonoChoiceButton::genericItemChooserSelected(GenericItemChooser *comp, int index)
{
    setSelectedItemIndex(index);
    
    int ident = index < idList.size() ? idList[index] : 0;
    
    listeners.call (&SonoChoiceButton::Listener::choiceButtonSelected, this, index, ident);
    
    if (CallOutBox* const dw = comp->findParentComponentOfClass<CallOutBox>()) {
        dw->dismiss();
    }

    setWantsKeyboardFocus(true);

    Timer::callAfterDelay(200, [this](){
        if (isShowing()) grabKeyboardFocus();
    });
}

void SonoChoiceButton::resized()
{
    SonoTextButton::resized();

    int xoff = 0;
    bool validImage = false;
    if (selIndex < items.size()) {
        if (items[selIndex].image.isValid()) {
            float imagesize = getHeight() - 8;
            xoff = imagesize;
            validImage = true;
        }
    }
    
    
    if (showArrow && getWidth()-(20 + xoff + 4) > 40) {
        textLabel->setBounds(4 + xoff, 2, getWidth() - 22, getHeight()-4 - xoff);
    }
    else if (!showArrow && getWidth()-(xoff + 4) > 40) {
        textLabel->setBounds(4 + xoff, 2, getWidth() - 8 - xoff, getHeight()-4 - xoff);        
    }
    else {
        textLabel->setSize(0, 0);
    }
}


void SonoChoiceButton::paint(Graphics & g)
{
    int width = getWidth();
    int height = getHeight();
    
    SonoTextButton::paint(g);
    
    if (showArrow) {
        Rectangle<int> arrowZone (width - 20, 0, 16, height);
        Path path;
        path.startNewSubPath (arrowZone.getX() + 3.0f, arrowZone.getCentreY() - 2.0f);
        path.lineTo (static_cast<float> (arrowZone.getCentreX()), arrowZone.getCentreY() + 3.0f);
        path.lineTo (arrowZone.getRight() - 3.0f, arrowZone.getCentreY() - 2.0f);
    
        g.setColour (findColour (ComboBox::arrowColourId).withAlpha ((isEnabled() ? 0.9f : 0.2f)));
        g.strokePath (path, PathStrokeType (2.0f));
    }
    
    if (selIndex < items.size()) {
        if (items[selIndex].image.isValid()) {
            float imagesize = height - 8;
            //g.drawImage(items[selIndex].image, Rectangle<float>(2, 4, imagesize, imagesize));
            g.drawImageWithin(items[selIndex].image, 2, 4, imagesize, imagesize, RectanglePlacement(RectanglePlacement::centred|RectanglePlacement::onlyReduceInSize));

        }
    }
}


void SonoChoiceButton::buttonClicked (Button* buttonThatWasClicked)
{
    if (items.isEmpty()) {
        listeners.call (&SonoChoiceButton::Listener::choiceButtonEmptyClick, this);
    }
    else {
        showPopup();
    }
}

void SonoChoiceButton::showPopup()
{
    auto chooser = std::make_unique<GenericItemChooser>(items);

    chooser->setRowHeight(std::min(getHeight(), 40));
    chooser->addListener(this);
    chooser->setCurrentRow(selIndex);
    chooser->setListTitle(getTitle());
    auto* chooserPtr = chooser.get();
    //DocumentWindow* const dw = this->findParentComponentOfClass<DocumentWindow>();
    Component* dw = this->findParentComponentOfClass<DocumentWindow>();

    if (!dw) {
        dw = this->findParentComponentOfClass<AudioProcessorEditor>();
    }
    if (!dw) {
        dw = this->findParentComponentOfClass<Component>();
    }

    chooser->setSize(jmin(chooser->getWidth(), dw->getWidth() - 16), jmin(chooser->getHeight(), dw->getHeight() - 20));


    Rectangle<int> bounds =  dw->getLocalArea(nullptr, getScreenBounds());


    CallOutBox & box = CallOutBox::launchAsynchronously (std::move(chooser), bounds , dw, false);
    box.setDismissalMouseClicksAreAlwaysConsumed(true);
    //box.setArrowSize(0);

    box.setTitle(getTitle());

    // Put focus on the list itself (on the current choice), not on the popup frame,
    // and bring it back here when the popup closes, even with Escape.
    chooserPtr->focusList();
    SonoAccessibility::returnFocusWhenClosed(box, *this);

    activeCalloutBox = &box;
}

bool SonoChoiceButton::isPopupActive() const
{
    return activeCalloutBox.get() != nullptr;
}


//==============================================================================
class SonoChoiceButtonAccessibilityHandler  : public AccessibilityHandler
{
public:
    explicit SonoChoiceButtonAccessibilityHandler (SonoChoiceButton& comboBoxToWrap)
        : AccessibilityHandler (comboBoxToWrap,
                                AccessibilityRole::comboBox,
                                getAccessibilityActions (comboBoxToWrap),
                                { std::make_unique<ValueInterface> (comboBoxToWrap) }),
          comboBox (comboBoxToWrap)
    {
    }

    class ValueInterface : public AccessibilityTextValueInterface
    {
    public:
        explicit ValueInterface (SonoChoiceButton& c) : choice (c) {}
        bool isReadOnly() const override                 { return true; }
        String getCurrentValueAsString() const override  { return choice.getCurrentText(); }
        void setValueAsString (const String&) override   {}
    private:
        SonoChoiceButton& choice;
    };

    AccessibleState getCurrentState() const override
    {
        auto state = AccessibilityHandler::getCurrentState().withExpandable();

        return comboBox.isPopupActive() ? state.withExpanded() : state.withCollapsed();
    }

    // The current choice is exposed as the value (below), the way screen readers expect
    // for combo boxes, rather than being folded into the name.
    String getTitle() const override  { return comboBox.getTitle().isNotEmpty() ? comboBox.getTitle() : comboBox.getButtonText(); }
    String getHelp() const override   { return comboBox.getTooltip(); }

private:
    static AccessibilityActions getAccessibilityActions (SonoChoiceButton& comboBox)
    {
        return AccessibilityActions().addAction (AccessibilityActionType::press,    [&comboBox] { comboBox.showPopup(); })
                                     .addAction (AccessibilityActionType::showMenu, [&comboBox] { comboBox.showPopup(); });
    }

    SonoChoiceButton& comboBox;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SonoChoiceButtonAccessibilityHandler)
};

std::unique_ptr<AccessibilityHandler> SonoChoiceButton::createAccessibilityHandler()
{
    return std::make_unique<SonoChoiceButtonAccessibilityHandler> (*this);
}
