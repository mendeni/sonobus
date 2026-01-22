#pragma once

#include <juce_osc/juce_osc.h>
#include <functional>
#include <map>

class OSCManager : private juce::OSCReceiver,
                   private juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    OSCManager();
    ~OSCManager();

    bool initializeReceiver(int port);
    bool initializeSender(const juce::String& targetIP, int port);
    void sendMessage(const juce::String& address, const juce::var& value);
    
    // Generic control registration
    using ControlCallback = std::function<void(const juce::OSCMessage&)>;
    void registerControl(const juce::String& address, ControlCallback callback);

private:
    void oscMessageReceived(const juce::OSCMessage& message) override;

    juce::OSCSender sender;
    bool senderConnected = false;  // Track sender connection state
    
    // Control registry for dynamic OSC message handling
    std::map<juce::String, ControlCallback> controlRegistry;
};
