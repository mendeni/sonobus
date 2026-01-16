#pragma once

#include <juce_osc/juce_osc.h>

class OSCManager : private juce::OSCReceiver,
                   private juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    OSCManager();
    ~OSCManager();

    bool initializeReceiver(int port);
    bool initializeSender(const juce::String& targetIP, int port);
    void sendMessage(const juce::String& address, const juce::var& value);

private:
    void oscMessageReceived(const juce::OSCMessage& message) override;

    juce::OSCSender sender;
    bool senderConnected = false;  // Track sender connection state
};
