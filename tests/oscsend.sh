#!/bin/bash -x

# Sends OSC messages to localhost port 6000
# Each message is followed by a sleep for UI control verification

# Audio Controls
oscsend localhost 6000 /DrySlider f 1.0
sleep 2
oscsend localhost 6000 /DrySlider f 0.5
sleep 2

oscsend localhost 6000 /OutGainSlider f 1.0
sleep 2
oscsend localhost 6000 /OutGainSlider f 0.5
sleep 2

# Main Control Buttons
oscsend localhost 6000 /MainMuteButton i 1
sleep 2
oscsend localhost 6000 /MainMuteButton i 0
sleep 2

oscsend localhost 6000 /MainRecvMuteButton i 1
sleep 2
oscsend localhost 6000 /MainRecvMuteButton i 0
sleep 2

oscsend localhost 6000 /MainPushToTalkButton i 1
sleep 2
oscsend localhost 6000 /MainPushToTalkButton i 0
sleep 2

# Metronome Controls
oscsend localhost 6000 /MetEnableButton i 1
sleep 2
oscsend localhost 6000 /MetEnableButton i 0
sleep 2

oscsend localhost 6000 /MetLevelSlider f 0.8
sleep 2
oscsend localhost 6000 /MetLevelSlider f 0.4
sleep 2

oscsend localhost 6000 /MetTempoSlider f 120.0
sleep 2
oscsend localhost 6000 /MetTempoSlider f 60.0
sleep 2

# -- not sure where this is located in UI
oscsend localhost 6000 /MetSyncButton i 1
sleep 2
oscsend localhost 6000 /MetSyncButton i 0
sleep 2

oscsend localhost 6000 /MetSyncFileButton i 1
sleep 2
oscsend localhost 6000 /MetSyncFileButton i 0
sleep 2

oscsend localhost 6000 /MetSendButton i 1
sleep 2
oscsend localhost 6000 /MetSendButton i 0
sleep 2

# Input Monitor Controls
oscsend localhost 6000 /InMuteButton i 1
sleep 2
oscsend localhost 6000 /InMuteButton i 0
sleep 2

oscsend localhost 6000 /InSoloButton i 1
sleep 2
oscsend localhost 6000 /InSoloButton i 0
sleep 2

# Utility Buttons
oscsend localhost 6000 /BufferMinButton i 1
sleep 2

oscsend localhost 6000 /RecvSyncButton i 1
sleep 2

oscsend localhost 6000 /RecordingButton i 1
sleep 2
oscsend localhost 6000 /RecordingButton i 0
sleep 2

# Example Command for Main Reverb Controls
oscsend localhost 6000 /MainReverbEnabled i 1
sleep 2
oscsend localhost 6000 /MainReverbEnabled i 0
sleep 2

oscsend localhost 6000 /ReverbLevelSlider f 1.0
sleep 2
oscsend localhost 6000 /ReverbLevelSlider f 0.5
sleep 2

oscsend localhost 6000 /ReverbSizeSlider f 1.0
sleep 2
oscsend localhost 6000 /ReverbSizeSlider f 0.5
sleep 2

oscsend localhost 6000 /ReverbDampingSlider f 1.0
sleep 2
oscsend localhost 6000 /ReverbDampingSlider f 0.5
sleep 2

oscsend localhost 6000 /ReverbPreDelaySlider f 20.0
sleep 2
oscsend localhost 6000 /ReverbPreDelaySlider f 60.0
sleep 2

# Options Options
oscsend localhost 6000 /OptionsDynamicResamplingButton i 1
sleep 2
oscsend localhost 6000 /OptionsDynamicResamplingButton i 0
sleep 2

oscsend localhost 6000 /OptionsUseSpecificUdpPortButton i 1
sleep 2
oscsend localhost 6000 /OptionsUseSpecificUdpPortButton i 0
sleep 2

oscsend localhost 6000 /OptionsUdpPortEditor i 12000
sleep 2
oscsend localhost 6000 /OptionsUdpPortEditor i 13000
sleep 2

oscsend localhost 6000 /OptionsOverrideSamplerateButton i 1
sleep 2
oscsend localhost 6000 /OptionsOverrideSamplerateButton i 0
sleep 2

oscsend localhost 6000 /OptionsShouldCheckForUpdateButton i 1
sleep 2
oscsend localhost 6000 /OptionsShouldCheckForUpdateButton i 0
sleep 2

oscsend localhost 6000 /OptionsAutoReconnectButton i 1
sleep 2
oscsend localhost 6000 /OptionsAutoReconnectButton i 0
sleep 2

oscsend localhost 6000 /OptionsSliderSnapToMouseButton i 1
sleep 2
oscsend localhost 6000 /OptionsSliderSnapToMouseButton i 0
sleep 2

oscsend localhost 6000 /OptionsInputLimiterButton i 1
sleep 2
oscsend localhost 6000 /OptionsInputLimiterButton i 0
sleep 2

oscsend localhost 6000 /OptionsDefaultLevelSlider f 0.73
sleep 2
oscsend localhost 6000 /OptionsDefaultLevelSlider f 0.1
sleep 2

oscsend localhost 6000 /OSCTargetIPAddress s "127.0.0.2"
sleep 2
oscsend localhost 6000 /OSCTargetIPAddress s "127.0.0.1"
sleep 2

oscsend localhost 6000 /OSCTargetPort i "9999"
sleep 2
oscsend localhost 6000 /OSCTargetPort i "6001"
sleep 2

# oscsend localhost 6000 /OSCReceivePort i "9998"
# sleep 2
# oscsend localhost 6000 /OSCReceivePort i "6000"
#sleep 2

oscsend localhost 6000 /OptionsMaxRecvPaddingSlider f 20.0
sleep 2
oscsend localhost 6000 /OptionsMaxRecvPaddingSlider f 10.0
sleep 2

oscsend localhost 6000 /OptionsAutoDropThreshSlider f 1.0
sleep 2
oscsend localhost 6000 /OptionsAutoDropThreshSlider f 33.0
sleep 2

oscsend localhost 6000 /BufferTimeSlider f 1.0
sleep 2
oscsend localhost 6000 /BufferTimeSlider f 33.0
sleep 2

oscsend localhost 6000 /OptionsChangeAllFormatButton i 1
sleep 2
oscsend localhost 6000 /OptionsChangeAllFormatButton i 0
sleep 2

# Recording Options
oscsend localhost 6000 /OptionsRecStealth i 1
sleep 2
oscsend localhost 6000 /OptionsRecStealth i 0
sleep 2

oscsend localhost 6000 /OptionsRecSelfSilenceMutedButton i 1
sleep 2
oscsend localhost 6000 /OptionsRecSelfSilenceMutedButton i 0
sleep 2

oscsend localhost 6000 /OptionsRecSelfPostFxButton i 1
sleep 2
oscsend localhost 6000 /OptionsRecSelfPostFxButton i 0
sleep 2

oscsend localhost 6000 /OptionsMetRecordedButton i 1
sleep 2
oscsend localhost 6000 /OptionsMetRecordedButton i 0
sleep 2

# -- Record features
oscsend localhost 6000 /OptionsRecSelfButton i 1
sleep 2
oscsend localhost 6000 /OptionsRecSelfButton i 0
sleep 2

oscsend localhost 6000 /OptionsRecOthersButton i 1
sleep 2
oscsend localhost 6000 /OptionsRecOthersButton i 0
sleep 2

oscsend localhost 6000 /OptionsRecMixMinusButton i 1
sleep 2
oscsend localhost 6000 /OptionsRecMixMinusButton i 0
sleep 2
