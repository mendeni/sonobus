// SPDX-License-Identifier: GPLv3-or-later WITH Appstore-exception
// Copyright (C) 2025 SonoBus Contributors

#include "OSCController.h"
#include "SonobusPluginProcessor.h"

OSCController::OSCController(SonobusAudioProcessor& processor)
    : mProcessor(processor)
{
    mReceiver = std::make_unique<juce::OSCReceiver>();
    mSender = std::make_unique<juce::OSCSender>();
}

OSCController::~OSCController()
{
    if (mReceiver)
    {
        mReceiver->disconnect();
        mReceiver->removeListener(this);
    }
    
    if (mSender)
    {
        mSender->disconnect();
    }
}

bool OSCController::setReceiveEnabled(bool enabled)
{
    juce::ScopedLock sl(mLock);
    
    if (enabled == mReceiveEnabled)
        return true;
    
    if (enabled)
    {
        if (mReceiver->connect(mReceivePort))
        {
            mReceiver->addListener(this);
            mReceiveEnabled = true;
            DBG("OSC receiver started on port " << mReceivePort);
            return true;
        }
        else
        {
            DBG("Failed to start OSC receiver on port " << mReceivePort);
            return false;
        }
    }
    else
    {
        mReceiver->disconnect();
        mReceiver->removeListener(this);
        mReceiveEnabled = false;
        DBG("OSC receiver stopped");
        return true;
    }
}

bool OSCController::setReceivePort(int port)
{
    if (port < 1024 || port > 65535)
        return false;
    
    juce::ScopedLock sl(mLock);
    
    bool wasEnabled = mReceiveEnabled;
    
    if (wasEnabled)
        setReceiveEnabled(false);
    
    mReceivePort = port;
    
    if (wasEnabled)
        return setReceiveEnabled(true);
    
    return true;
}

void OSCController::setSendHost(const juce::String& host)
{
    juce::ScopedLock sl(mLock);
    
    if (mSendHost == host)
        return;
    
    mSendHost = host;
    
    // Reconnect sender with new host
    mSender->disconnect();
    if (mSendHost.isNotEmpty() && mSendPort > 0)
    {
        if (mSender->connect(mSendHost, mSendPort))
        {
            DBG("OSC sender connected to " << mSendHost << ":" << mSendPort);
            mSendEnabled = true;
        }
        else
        {
            DBG("Failed to connect OSC sender to " << mSendHost << ":" << mSendPort);
            mSendEnabled = false;
        }
    }
}

void OSCController::setSendPort(int port)
{
    if (port < 1024 || port > 65535)
        return;
    
    juce::ScopedLock sl(mLock);
    
    if (mSendPort == port)
        return;
    
    mSendPort = port;
    
    // Reconnect sender with new port
    mSender->disconnect();
    if (mSendHost.isNotEmpty() && mSendPort > 0)
    {
        if (mSender->connect(mSendHost, mSendPort))
        {
            DBG("OSC sender connected to " << mSendHost << ":" << mSendPort);
            mSendEnabled = true;
        }
        else
        {
            DBG("Failed to connect OSC sender to " << mSendHost << ":" << mSendPort);
            mSendEnabled = false;
        }
    }
}

void OSCController::setSendEnabled(bool enabled)
{
    juce::ScopedLock sl(mLock);
    
    if (enabled && !mSendEnabled)
    {
        // Try to connect
        if (mSendHost.isNotEmpty() && mSendPort > 0)
        {
            if (mSender->connect(mSendHost, mSendPort))
            {
                DBG("OSC sender connected to " << mSendHost << ":" << mSendPort);
                mSendEnabled = true;
            }
            else
            {
                DBG("Failed to connect OSC sender to " << mSendHost << ":" << mSendPort);
                mSendEnabled = false;
            }
        }
    }
    else if (!enabled && mSendEnabled)
    {
        mSender->disconnect();
        mSendEnabled = false;
        DBG("OSC sender disconnected");
    }
}

bool OSCController::sendParameterChange(const juce::String& paramId, float value)
{
    juce::String address = "/sonobus/" + paramId;
    juce::OSCMessage message(address);
    message.addFloat32(value);
    
    return sendMessage(address, message);
}

bool OSCController::sendMessage(const juce::String& address, const juce::OSCMessage& message)
{
    juce::ScopedLock sl(mLock);
    
    if (!mSender->send(message))
    {
        DBG("Failed to send OSC message to " << address);
        return false;
    }
    
    return true;
}

void OSCController::oscMessageReceived(const juce::OSCMessage& message)
{
    handleIncomingMessage(message);
}

void OSCController::handleIncomingMessage(const juce::OSCMessage& message)
{
    juce::String address = message.getAddressPattern().toString();
    
    DBG("OSC message received: " << address);
    
    // Check if it's a SonoBus parameter message
    if (address.startsWith("/sonobus/"))
    {
        juce::String paramName = address.substring(9); // Remove "/sonobus/" prefix
        
        if (message.size() > 0)
        {
            // Handle different argument types
            if (message[0].isFloat32())
            {
                float value = message[0].getFloat32();
                
                // Get the parameter from the processor
                auto* param = mProcessor.getValueTreeState().getParameter(paramName);
                if (param != nullptr)
                {
                    param->setValueNotifyingHost(value);
                    DBG("OSC: Set parameter " << paramName << " to " << value);
                    
                    // Send feedback
                    sendFeedback(address, value);
                }
                else
                {
                    DBG("OSC: Unknown parameter " << paramName);
                }
            }
            else if (message[0].isInt32())
            {
                float value = static_cast<float>(message[0].getInt32());
                
                auto* param = mProcessor.getValueTreeState().getParameter(paramName);
                if (param != nullptr)
                {
                    // Pass integer as float directly (for boolean/choice parameters)
                    param->setValueNotifyingHost(value);
                    DBG("OSC: Set parameter " << paramName << " to " << value);
                    
                    sendFeedback(address, value);
                }
            }
        }
    }
    // Handle ping message
    else if (address == "/sonobus/ping")
    {
        juce::OSCMessage pong("/sonobus/pong");
        pong.addString("SonoBus OSC");
        sendMessage("/sonobus/pong", pong);
        DBG("OSC: Responded to ping");
    }
}

void OSCController::sendFeedback(const juce::String& address, float value)
{
    juce::OSCMessage feedback(address + "/feedback");
    feedback.addFloat32(value);
    sendMessage(address + "/feedback", feedback);
}

void OSCController::saveState(juce::ValueTree& parentTree)
{
    juce::ValueTree oscTree("OSC");
    
    oscTree.setProperty("receiveEnabled", mReceiveEnabled, nullptr);
    oscTree.setProperty("receivePort", mReceivePort, nullptr);
    oscTree.setProperty("sendEnabled", mSendEnabled, nullptr);
    oscTree.setProperty("sendHost", mSendHost, nullptr);
    oscTree.setProperty("sendPort", mSendPort, nullptr);
    
    parentTree.appendChild(oscTree, nullptr);
}

void OSCController::loadState(const juce::ValueTree& parentTree)
{
    auto oscTree = parentTree.getChildWithName("OSC");
    if (!oscTree.isValid())
        return;
    
    mReceiveEnabled = oscTree.getProperty("receiveEnabled", false);
    
    // Validate and load receive port
    int loadedReceivePort = oscTree.getProperty("receivePort", 9951);
    if (loadedReceivePort >= 1024 && loadedReceivePort <= 65535)
    {
        mReceivePort = loadedReceivePort;
    }
    else
    {
        DBG("OSC: Invalid receive port in saved state, using default");
        mReceivePort = 9951;
    }
    
    mSendHost = oscTree.getProperty("sendHost", "127.0.0.1").toString();
    
    // Validate and load send port
    int loadedSendPort = oscTree.getProperty("sendPort", 9952);
    if (loadedSendPort >= 1024 && loadedSendPort <= 65535)
    {
        mSendPort = loadedSendPort;
    }
    else
    {
        DBG("OSC: Invalid send port in saved state, using default");
        mSendPort = 9952;
    }
    
    // Load send enabled state
    mSendEnabled = oscTree.getProperty("sendEnabled", false);
    
    // Apply the loaded state
    if (mReceiveEnabled)
    {
        setReceiveEnabled(true);
    }
    
    // Connect sender if enabled
    if (mSendEnabled && mSendHost.isNotEmpty() && mSendPort > 0)
    {
        if (mSender->connect(mSendHost, mSendPort))
        {
            DBG("OSC sender restored connection to " << mSendHost << ":" << mSendPort);
        }
        else
        {
            DBG("Failed to restore OSC sender connection");
            mSendEnabled = false;
        }
    }
}
