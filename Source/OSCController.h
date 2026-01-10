// SPDX-License-Identifier: GPLv3-or-later WITH Appstore-exception
// Copyright (C) 2025 SonoBus Contributors

#pragma once

#include "JuceHeader.h"

class SonobusAudioProcessor;

/**
 * OSCController manages Open Sound Control communication for SonoBus.
 * Provides both sending and receiving OSC messages to enable remote control
 * and integration with other OSC-compatible applications and hardware.
 */
class OSCController : public juce::OSCReceiver::Listener<juce::OSCReceiver::MessageLoopCallback>,
                      public juce::AudioProcessorValueTreeState::Listener
{
public:
    OSCController(SonobusAudioProcessor& processor);
    ~OSCController() override;

    // Configuration
    bool setReceiveEnabled(bool enabled);
    bool isReceiveEnabled() const { return mReceiveEnabled; }
    
    bool setReceivePort(int port);
    int getReceivePort() const { return mReceivePort; }
    
    void setSendHost(const juce::String& host);
    juce::String getSendHost() const { return mSendHost; }
    
    void setSendPort(int port);
    int getSendPort() const { return mSendPort; }
    
    // Enable/disable sending parameter changes via OSC
    void setSendEnabled(bool enabled);
    bool isSendEnabled() const { return mSendEnabled; }
    
    // Sending OSC messages
    bool sendParameterChange(const juce::String& paramId, float value);
    bool sendMessage(const juce::String& address, const juce::OSCMessage& message);
    
    // OSC Receiver callback
    void oscMessageReceived(const juce::OSCMessage& message) override;
    
    // Parameter listener callback
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    
    // State persistence
    void saveState(juce::ValueTree& parentTree);
    void loadState(const juce::ValueTree& parentTree);

private:
    void handleIncomingMessage(const juce::OSCMessage& message);
    void sendFeedback(const juce::String& address, float value);
    
    SonobusAudioProcessor& mProcessor;
    
    std::unique_ptr<juce::OSCReceiver> mReceiver;
    std::unique_ptr<juce::OSCSender> mSender;
    
    bool mReceiveEnabled = false;
    int mReceivePort = 9951;
    bool mSendEnabled = false;
    juce::String mSendHost = "127.0.0.1";
    int mSendPort = 9952;
    
    juce::CriticalSection mLock;
    bool mSuppressFeedback = false;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OSCController)
};
