// SPDX-License-Identifier: GPLv3-or-later WITH Appstore-exception
// Screen reader (JAWS / NVDA / VoiceOver) helpers for SonoBus.

#pragma once

#include "JuceHeader.h"

namespace SonoAccessibility
{
    /** Scrolls every Viewport that encloses comp so that comp is fully visible.

        JUCE reports any control that lies outside the visible part of its scrolling
        parent as "offscreen" to the screen reader, and reports keyboard focus on such
        a control as focus on its parent instead. Keeping the focused control scrolled
        into view keeps the screen reader's focus where the keyboard focus really is.
    */
    void scrollIntoView (Component* comp);

    /** A keyboard focus traverser that scrolls the control about to receive focus into
        view before it is focused. Return one of these from createKeyboardFocusTraverser()
        in any keyboard focus container that holds scrolling content.
    */
    class ScrollingKeyboardFocusTraverser : public KeyboardFocusTraverser
    {
    public:
        Component* getNextComponent (Component* current) override;
        Component* getPreviousComponent (Component* current) override;
        Component* getDefaultComponent (Component* parentComponent) override;
    };

    /** Installs an app-wide listener that scrolls any newly focused control into view
        (covers focus moved by mouse, code, or the screen reader itself). Safe to call
        more than once.
    */
    void installFocusScroller();

    /** Asks the screen reader to speak a message. */
    void announce (const String& message,
                   AccessibilityHandler::AnnouncementPriority priority = AccessibilityHandler::AnnouncementPriority::medium);

    /** When popup is deleted (for example a CallOutBox being dismissed), moves keyboard
        focus back to returnTo, unless the user has already put focus somewhere else.
    */
    void returnFocusWhenClosed (Component& popup, Component& returnTo);

    /** A ListBox that speaks its current item when it gets keyboard focus and when the
        arrow keys move through it ("Jazz Jam, 3 active users, 2 of 5"), and says so when
        the list is empty. JAWS often stays silent on plain JUCE lists.
        If nothing is selected when it gets focus, the first item is selected (selection
        alone never triggers an action; Enter does).
    */
    class SpeakingListBox : public ListBox
    {
    public:
        explicit SpeakingListBox (const String& componentName = {}, const String& emptyMessage = {});

        void setEmptyMessage (const String& message) { emptyMessage = message; }

        void focusGained (FocusChangeType cause) override;
        bool keyPressed (const KeyPress& key) override;

        /** Speaks the selected item and its position, or the empty message. */
        void speakCurrentRow();

    private:
        String emptyMessage;
    };

    /** Makes JUCE's AudioDeviceSelectorComponent work better with screen readers:
        - gives every dropdown and list the name of the label shown next to it
          (and hides that label so it isn't read twice),
        - names the "Select All" buttons after the channel list they belong to,
        - lets Space or Enter turn a channel on or off and speaks the new state,
        - puts keyboard focus back after the panel rebuilds itself on a device change.
    */
    class AudioDeviceSelectorHelper : private ChangeListener,
                                      private FocusChangeListener,
                                      private ComponentListener,
                                      private KeyListener
    {
    public:
        AudioDeviceSelectorHelper (AudioDeviceSelectorComponent& selector, AudioDeviceManager& manager);
        ~AudioDeviceSelectorHelper() override;

        /** Re-applies names and key handling. Called automatically after device
            changes and resizes. */
        void refresh();

    private:
        void changeListenerCallback (ChangeBroadcaster*) override;
        void globalFocusChanged (Component* focusedComponent) override;
        void componentMovedOrResized (Component&, bool wasMoved, bool wasResized) override;
        void componentVisibilityChanged (Component&) override;
        bool keyPressed (const KeyPress& key, Component* originatingComponent) override;

        void afterDeviceChange();
        void restoreFocusIfLost();

        Component::SafePointer<AudioDeviceSelectorComponent> selector;
        AudioDeviceManager& manager;

        Component::SafePointer<Component> lastFocused;
        String lastFocusedName;
        bool refreshing = false;

        JUCE_DECLARE_WEAK_REFERENCEABLE (AudioDeviceSelectorHelper)
        JUCE_DECLARE_NON_COPYABLE (AudioDeviceSelectorHelper)
    };
}
