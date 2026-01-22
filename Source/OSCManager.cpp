#include "OSCManager.h"

OSCManager::OSCManager()
{
    juce::Logger::writeToLog("OSCManager initialized.");
}

OSCManager::~OSCManager()
{
    sender.disconnect();
    disconnect();
}

// Initialize Receiver
bool OSCManager::initializeReceiver(int port)
{
    if (!connect(port))
    {
        juce::Logger::writeToLog("Receiver failed to connect on port " + juce::String(port));
        return false;
    }

    addListener(this, "/volumeControl");
    addListener(this, "/OutGainSlider");
    addListener(this, "/MainMuteButton");
    addListener(this, "/RecvSyncButton");
    juce::Logger::writeToLog("Receiver connected on port " + juce::String(port));
    return true;
}

// Initialize Sender
bool OSCManager::initializeSender(const juce::String& targetIP, int port)
{
    senderConnected = sender.connect(targetIP, port);
    if (!senderConnected)
    {
        juce::Logger::writeToLog("Sender failed to connect to " + targetIP + ":" + juce::String(port));
    }
    return senderConnected;
}

// Send Message
void OSCManager::sendMessage(const juce::String& address, const juce::var& value)
{
    if (senderConnected)
    {
        if (value.isDouble())
        {
            sender.send(address, static_cast<float>(value));  // Convert double to float
        }
        else if (value.isInt())
        {
            sender.send(address, static_cast<int>(value));
        }
        else if (value.isString())
        {
            sender.send(address, value.toString());
        }
        else
        {
            juce::Logger::writeToLog("Unsupported var type in sendMessage for: " + address);
        }
    }
    else
    {
        juce::Logger::writeToLog("OSC Sender is not connected! Cannot send message to: " + address);
    }
}

// Register Control
void OSCManager::registerControl(const juce::String& address, ControlCallback callback)
{
    controlRegistry[address] = callback;
    juce::Logger::writeToLog("Registered control for OSC address: " + address);
}

// Handle Received Messages
void OSCManager::oscMessageReceived(const juce::OSCMessage& message)
{
    juce::String address = message.getAddressPattern().toString();
    juce::Logger::writeToLog("Incoming OSC message: " + address);
    
    // Check if a callback is registered for this address
    auto it = controlRegistry.find(address);
    if (it != controlRegistry.end())
    {
        // Call the registered callback
        it->second(message);
    }
    else
    {
        juce::Logger::writeToLog("No handler registered for OSC address: " + address);
    }
}
