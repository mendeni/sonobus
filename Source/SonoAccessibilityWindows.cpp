// SPDX-License-Identifier: GPLv3-or-later WITH Appstore-exception
// Windows-only: send spoken announcements to the running screen reader (JAWS, NVDA,
// Narrator) as UI Automation notification events, so they are spoken in the screen
// reader's own voice. JUCE's AccessibilityHandler::postAnnouncement uses the separate
// Windows SAPI voice instead.
//
// Kept in its own file so <windows.h> never meets JuceHeader.h.

#ifdef _WIN32

#ifndef NOMINMAX
 #define NOMINMAX
#endif
#include <windows.h>
#include <oleauto.h>
#include <uiautomation.h>

namespace SonoAccessibilityWindows
{
    using RaiseNotificationFn = HRESULT (WINAPI*) (IRawElementProviderSimple*, NotificationKind,
                                                   NotificationProcessing, BSTR, BSTR);

    static RaiseNotificationFn getRaiseNotification()
    {
        // Available from Windows 10 1709. Looked up at runtime so older systems still start.
        static RaiseNotificationFn fn = []() -> RaiseNotificationFn
        {
            if (auto module = LoadLibraryW (L"UIAutomationCore.dll"))
                return reinterpret_cast<RaiseNotificationFn> (GetProcAddress (module, "UiaRaiseNotificationEvent"));
            return nullptr;
        }();

        return fn;
    }

    bool isAvailable()
    {
        return getRaiseNotification() != nullptr;
    }

    // nativeHandle: what juce::AccessibilityHandler::getNativeImplementation() returns on
    // Windows. That object is a COM object whose first base is IRawElementProviderSimple,
    // so it can be treated as an IUnknown and asked for that interface.
    // priority: 0 = low, 1 = medium, 2 = high
    bool raiseNotification (void* nativeHandle, const wchar_t* text, int priority)
    {
        auto raise = getRaiseNotification();

        if (raise == nullptr || nativeHandle == nullptr || text == nullptr || *text == 0)
            return false;

        auto* unknown = static_cast<IUnknown*> (nativeHandle);
        IRawElementProviderSimple* provider = nullptr;

        if (FAILED (unknown->QueryInterface (__uuidof (IRawElementProviderSimple), reinterpret_cast<void**> (&provider)))
            || provider == nullptr)
            return false;

        // high: always spoken, ahead of other speech
        // medium (e.g. moving through a list): replaces an older, not yet spoken message
        // low: spoken when there's a gap
        const auto processing = priority >= 2 ? NotificationProcessing_ImportantAll
                              : priority == 1 ? NotificationProcessing_MostRecent
                                              : NotificationProcessing_All;

        auto message  = SysAllocString (text);
        auto activity = SysAllocString (L"SonoBus");

        const auto hr = raise (provider, NotificationKind_Other, processing, message, activity);

        SysFreeString (message);
        SysFreeString (activity);
        provider->Release();

        return SUCCEEDED (hr);
    }
}

#endif // _WIN32
