# SonoBus OSC Commands Documentation

This document describes all available OSC (Open Sound Control) commands for controlling SonoBus remotely.

## Overview

SonoBus supports bidirectional OSC communication, allowing external controllers to both send commands to control the application and receive status updates when controls change.

## Configuration

OSC can be configured in the Options tab:
- **Enable OSC**: Toggle OSC functionality on/off
- **Target IP Address**: IP address to send OSC messages to (default: 127.0.0.1)
- **Target Port**: Port to send OSC messages to (default: 9000)
- **Receive Port**: Port to listen for incoming OSC messages (default: 9001)

## OSC Address Format

All OSC addresses follow the pattern: `/<ControlName>`

## Control Types

### Sliders (Float Values)
Sliders accept and send float values representing the parameter value.
- **Send**: `/address <float value>`
- **Receive**: Application sends float value when slider changes

### Toggle Buttons (On/Off State)
Toggle buttons accept and send integer values (0 = off, 1 = on).
- **Send**: `/address <int 0|1>`
- **Receive**: Application sends 0 or 1 when toggle state changes

### Push Buttons (Trigger Actions)
Push buttons accept integer value 1 to trigger their action.
- **Send**: `/address <int 1>`
- **Receive**: Application sends 1 when button is clicked

### Push-Hold Buttons (Press/Release)
Push-hold buttons accept integer values (1 = press, 0 = release).
- **Send**: `/address <int 0|1>`
- **Receive**: Application sends 1 on press, 0 on release

### Choice Buttons (Selection)
Choice buttons accept and send integer values representing the selected option ID.
- **Send**: `/address <int option_id>`
- **Receive**: Application sends option ID when selection changes

## Main UI Controls

### Audio Controls

#### `/DrySlider`
**Type**: Slider  
**Description**: Controls the monitor (dry) level - your own audio that you hear  
**Data Type**: Float  
**Range**: Audio level in decibels  
**Parameter**: `paramDry`

#### `/OutGainSlider`
**Type**: Slider  
**Description**: Controls the output (wet) level - mix of all incoming audio  
**Data Type**: Float  
**Range**: Audio level in decibels  
**Parameter**: `paramWet`

### Main Control Buttons

#### `/MainMuteButton`
**Type**: Toggle Button  
**Description**: Mutes/unmutes sending your audio to others  
**Data Type**: Integer (0 = unmuted/sending, 1 = muted/not sending)  
**Parameter**: `paramMainSendMute`

#### `/MainRecvMuteButton`
**Type**: Toggle Button  
**Description**: Mutes/unmutes receiving audio from all other users  
**Data Type**: Integer (0 = unmuted/receiving, 1 = muted/not receiving)  
**Parameter**: `paramMainRecvMute`

#### `/MainPushToTalkButton`
**Type**: Push-Hold Button  
**Description**: Push to talk - temporarily unmutes sending and mutes receiving  
**Data Type**: Integer (1 = press/talk, 0 = release/listen)  
**Behavior**: 
- When pressed (1): Unmutes send, mutes receive
- When released (0): Restores previous send mute state, unmutes receive

### Metronome Controls

#### `/MetEnableButton`
**Type**: Toggle Button  
**Description**: Enables/disables the metronome  
**Data Type**: Integer (0 = disabled, 1 = enabled)  
**Parameter**: `paramMetEnabled`

#### `/MetLevelSlider`
**Type**: Slider  
**Description**: Controls the metronome level/volume  
**Data Type**: Float  
**Range**: Audio level  
**Parameter**: `paramMetGain`

#### `/MetTempoSlider`
**Type**: Slider  
**Description**: Controls the metronome tempo in BPM  
**Data Type**: Float  
**Range**: Tempo in beats per minute  
**Parameter**: `paramMetTempo`

#### `/MetSyncButton`
**Type**: Toggle Button  
**Description**: Synchronizes metronome to host DAW tempo  
**Data Type**: Integer (0 = not synced, 1 = synced to host)  
**Parameter**: `paramSyncMetToHost`

#### `/MetSyncFileButton`
**Type**: Toggle Button  
**Description**: Synchronizes metronome to file playback tempo  
**Data Type**: Integer (0 = not synced, 1 = synced to file)  
**Parameter**: `paramSyncMetToFilePlayback`

### Input Monitor Controls

#### `/InMuteButton`
**Type**: Toggle Button  
**Description**: Mutes/unmutes your input monitor (what you hear of your own audio)  
**Data Type**: Integer (0 = unmuted, 1 = muted)  
**Parameter**: `paramMainInMute`

#### `/InSoloButton`
**Type**: Toggle Button  
**Description**: Solos your input monitor  
**Data Type**: Integer (0 = not soloed, 1 = soloed)  
**Parameter**: `paramMainMonitorSolo`

### Utility Buttons

#### `/BufferMinButton`
**Type**: Push Button  
**Description**: Resets the jitter buffer to minimum for all connected users  
**Data Type**: Integer (1 to trigger)  
**Action**: Resets all peer jitter buffers

#### `/RecvSyncButton`
**Type**: Push Button  
**Description**: Synchronizes receive latency for all users  
**Data Type**: Integer (1 to trigger)  
**Action**: Adjusts all peer jitter buffers to match the highest latency

#### `/RecordingButton`
**Type**: Toggle Button  
**Description**: Starts/stops recording audio to file  
**Data Type**: Integer (0 = stop recording, 1 = start recording)  
**Behavior**: Toggles recording state
- When turned on: Starts recording with current settings
- When turned off: Stops recording and saves file

### Main Reverb Controls

#### `/MainReverbEnabled`
**Type**: Toggle Button  
**Description**: Enables/disables the main reverb effect  
**Data Type**: Integer (0 = disabled, 1 = enabled)  
**Parameter**: `paramMainReverbEnabled`

#### `/ReverbLevelSlider`
**Type**: Slider  
**Description**: Controls the reverb level/mix  
**Data Type**: Float  
**Range**: Audio level  
**Parameter**: `paramMainReverbLevel`

#### `/ReverbSizeSlider`
**Type**: Slider  
**Description**: Controls the reverb room size  
**Data Type**: Float  
**Range**: Room size parameter  
**Parameter**: `paramMainReverbSize`

#### `/ReverbDampingSlider`
**Type**: Slider  
**Description**: Controls the reverb damping (high frequency absorption)  
**Data Type**: Float  
**Range**: Damping parameter  
**Parameter**: `paramMainReverbDamping`

#### `/ReverbPreDelaySlider`
**Type**: Slider  
**Description**: Controls the reverb pre-delay time  
**Data Type**: Float  
**Range**: Pre-delay time in milliseconds  
**Parameter**: `paramMainReverbPreDelay`

### File Playback Controls

#### `/FileSendButton`
**Type**: Toggle Button  
**Description**: Enables/disables sending file playback audio to all users  
**Data Type**: Integer (0 = disabled, 1 = enabled)  
**Parameter**: `paramSendFileAudio`

#### `/PlaybackSlider`
**Type**: Slider  
**Description**: Controls the file playback level/gain  
**Data Type**: Float  
**Range**: Audio level (0.0 - 2.0, where 1.0 is unity gain)  
**Action**: Sets file playback volume

#### `/FileMonitorSlider`
**Type**: Slider  
**Description**: Controls the file playback monitor level (what you hear)  
**Data Type**: Float  
**Range**: Audio level  
**Action**: Sets file playback monitor volume

### Soundboard Controls

#### `/SoundboardSendButton`
**Type**: Toggle Button  
**Description**: Enables/disables sending soundboard audio to all users  
**Data Type**: Integer (0 = disabled, 1 = enabled)  
**Parameter**: `paramSendSoundboardAudio`

#### `/SoundboardLevelSlider`
**Type**: Slider  
**Description**: Controls the soundboard output level/gain  
**Data Type**: Float  
**Range**: Audio level  
**Action**: Sets soundboard output volume

#### `/SoundboardMonitorSlider`
**Type**: Slider  
**Description**: Controls the soundboard monitor level (what you hear)  
**Data Type**: Float  
**Range**: Audio level  
**Action**: Sets soundboard monitor volume

### Metronome Advanced Controls

#### `/MetSendButton`
**Type**: Toggle Button  
**Description**: Enables/disables sending metronome to all users  
**Data Type**: Integer (0 = disabled, 1 = enabled)  
**Parameter**: `paramSendMetAudio`

#### `/MetPanSlider`
**Type**: Slider  
**Description**: Controls the metronome stereo pan position  
**Data Type**: Float  
**Range**: -1.0 (full left) to 1.0 (full right), 0.0 is center  
**Action**: Sets metronome pan position

#### `/MetMonitorSlider`
**Type**: Slider  
**Description**: Controls the metronome monitor level (what you hear)  
**Data Type**: Float  
**Range**: Audio level  
**Action**: Sets metronome monitor volume

### Input Reverb Controls

#### `/InReverbButton`
**Type**: Toggle Button  
**Description**: Opens/closes the input reverb configuration panel  
**Data Type**: Integer (1 to trigger)  
**Action**: Toggles input reverb panel visibility

#### `/InputReverbLevel`
**Type**: Slider  
**Description**: Controls the input reverb level/mix  
**Data Type**: Float  
**Range**: Audio level  
**Parameter**: `paramInputReverbLevel`

#### `/InputReverbSize`
**Type**: Slider  
**Description**: Controls the input reverb room size  
**Data Type**: Float  
**Range**: Room size parameter  
**Parameter**: `paramInputReverbSize`

#### `/InputReverbDamping`
**Type**: Slider  
**Description**: Controls the input reverb damping (high frequency absorption)  
**Data Type**: Float  
**Range**: Damping parameter  
**Parameter**: `paramInputReverbDamping`

#### `/InputReverbPreDelay`
**Type**: Slider  
**Description**: Controls the input reverb pre-delay time  
**Data Type**: Float  
**Range**: Pre-delay time in milliseconds  
**Parameter**: `paramInputReverbPreDelay`

### Monitor Delay Controls

#### `/MonDelayButton`
**Type**: Toggle Button  
**Description**: Toggles monitor delay enabled on all input groups  
**Data Type**: Integer (0 = disabled, 1 = enabled)  
**Action**: Enables/disables monitor delay for all inputs

## Options Tab Controls

### Audio Options

#### `/OptionsDynamicResamplingButton`
**Type**: Toggle Button  
**Description**: Enables/disables drift correction (dynamic resampling)  
**Data Type**: Integer (0 = disabled, 1 = enabled)  
**Parameter**: `paramDynamicResampling`  
**Note**: Not recommended for most users

#### `/OptionsInputLimiterButton`
**Type**: Toggle Button  
**Description**: Enables/disables the input FX limiter  
**Data Type**: Integer (0 = disabled, 1 = enabled)  
**Action**: Applies limiter to all input groups

#### `/OptionsDefaultLevelSlider`
**Type**: Slider  
**Description**: Sets the default level for new peer connections  
**Data Type**: Float  
**Range**: Audio level in decibels  
**Parameter**: `paramDefaultPeerLevel`

#### `/OptionsMaxRecvPaddingSlider`
**Type**: Slider  
**Description**: Sets the maximum receive padding in milliseconds  
**Data Type**: Float  
**Range**: 0.0 - 500.0 ms  
**Parameter**: `paramMaxRecvPaddingMs`

### Connection Options

#### `/OptionsAutoReconnectButton`
**Type**: Toggle Button  
**Description**: Enables/disables automatic reconnection to the last group  
**Data Type**: Integer (0 = disabled, 1 = enabled)  
**Parameter**: `paramAutoReconnectLast`

### Default Format Options

#### `/OptionsAutosizeDefaultChoice`
**Type**: Choice Button  
**Description**: Sets the default auto network buffer setting for new connections  
**Data Type**: Integer (option ID)  
**Parameter**: `paramDefaultAutoNetbuf`  
**Options**:
- 0: Off
- 1: Auto
- 2: Auto Increased

#### `/OptionsFormatChoiceDefaultChoice`
**Type**: Choice Button  
**Description**: Sets the default audio format/quality for new connections  
**Data Type**: Integer (option ID)  
**Parameter**: `paramDefaultSendQual`  
**Options**: Various codec quality settings (PCM, Opus at different bitrates)

#### `/BufferTimeSlider`
**Type**: Slider  
**Description**: Sets the default jitter buffer size in milliseconds  
**Data Type**: Float  
**Range**: Buffer time in milliseconds  
**Parameter**: `paramDefaultNetbufMs`

#### `/OptionsAutoDropThreshSlider`
**Type**: Slider  
**Description**: Controls auto-jitter buffer adjustment sensitivity based on dropout rate  
**Data Type**: Float  
**Range**: 1.0 - 20.0 seconds  
**Note**: Threshold for automatic buffer size increases when dropouts occur

### UI Options

#### `/OptionsDisableShortcutButton`
**Type**: Toggle Button  
**Description**: Enables/disables keyboard shortcuts  
**Data Type**: Integer (0 = shortcuts enabled, 1 = shortcuts disabled)  
**Action**: Toggles keyboard shortcut functionality

#### `/OptionsSliderSnapToMouseButton`
**Type**: Toggle Button  
**Description**: Controls whether sliders snap to clicked position  
**Data Type**: Integer (0 = no snap, 1 = snap to mouse)  
**Action**: Changes slider behavior for all sliders

#### `/OptionsChangeAllFormatButton`
**Type**: Toggle Button  
**Description**: When enabled, changing default codec also changes existing peer connections  
**Data Type**: Integer (0 = disabled, 1 = enabled)  
**Action**: Controls codec change behavior

### System Options

#### `/OptionsUseSpecificUdpPortButton`
**Type**: Toggle Button  
**Description**: Enables/disables use of a specific UDP port  
**Data Type**: Integer (0 = system-chosen port, 1 = use specific port)  
**Action**: Toggles specific UDP port usage

#### `/OptionsUdpPortEditor`
**Type**: Text Input  
**Description**: Sets the specific UDP port to use (when enabled)  
**Data Type**: Integer (port number)  
**Range**: 1-65535  
**Note**: Only active when UseSpecificUdpPort is enabled

#### `/OptionsOverrideSamplerateButton`
**Type**: Toggle Button  
**Description**: Enables/disables sample rate override  
**Data Type**: Integer (0 = use device rate, 1 = override)  
**Action**: Toggles sample rate override (standalone app only)

#### `/OptionsShouldCheckForUpdateButton`
**Type**: Toggle Button  
**Description**: Enables/disables automatic update checking  
**Data Type**: Integer (0 = no auto-check, 1 = auto-check)  
**Action**: Controls automatic update check behavior (standalone app only)

### OSC Configuration

#### `/OSCTargetIPAddress`
**Type**: Text Input  
**Description**: Sets the IP address for outbound OSC messages  
**Data Type**: String (IP address)  
**Default**: "127.0.0.1"

#### `/OSCTargetPort`
**Type**: Text Input  
**Description**: Sets the port for outbound OSC messages  
**Data Type**: Integer (port number)  
**Range**: 1-65535  
**Default**: 6001

#### `/OSCReceivePort`
**Type**: Text Input  
**Description**: Sets the port for receiving OSC messages  
**Data Type**: Integer (port number)  
**Range**: 1-65535  
**Default**: 6000

## Recording Tab Controls

### Recording Options

#### `/OptionsRecStealth`
**Type**: Toggle Button  
**Description**: Enables/disables stealth recording (no visual indication to others)  
**Data Type**: Integer (0 = disabled, 1 = enabled)  
**Action**: Sets stealth recording mode

#### `/OptionsMetRecordedButton`
**Type**: Toggle Button  
**Description**: Enables/disables recording the metronome to file  
**Data Type**: Integer (0 = not recorded, 1 = recorded)  
**Parameter**: `paramMetIsRecorded`

#### `/OptionsRecSelfPostFxButton`
**Type**: Toggle Button  
**Description**: Records your audio after FX processing (post-FX)  
**Data Type**: Integer (0 = pre-FX, 1 = post-FX)  
**Action**: Controls recording point for self audio

#### `/OptionsRecSelfSilenceMutedButton`
**Type**: Toggle Button  
**Description**: Silences self recording when muted  
**Data Type**: Integer (0 = record when muted, 1 = silence when muted)  
**Action**: Controls self recording behavior when muted

#### `/OptionsRecMixButton`
**Type**: Toggle Button  
**Description**: Enables/disables recording the output mix  
**Data Type**: Integer (0 = disabled, 1 = enabled)  
**Action**: Includes/excludes output mix in recording

#### `/OptionsRecSelfButton`
**Type**: Toggle Button  
**Description**: Enables/disables recording your own audio (dry)  
**Data Type**: Integer (0 = disabled, 1 = enabled)  
**Action**: Includes/excludes your audio in recording

#### `/OptionsRecOthersButton`
**Type**: Toggle Button  
**Description**: Enables/disables recording individual user tracks  
**Data Type**: Integer (0 = disabled, 1 = enabled)  
**Action**: Includes/excludes individual user tracks in recording

#### `/OptionsRecMixMinusButton`
**Type**: Toggle Button  
**Description**: Enables/disables recording the full mix without yourself  
**Data Type**: Integer (0 = disabled, 1 = enabled)  
**Action**: Includes/excludes the output mix minus your own audio in recording

**Note**: At least one recording option must be enabled. If all are disabled, RecMix is automatically enabled.

## Example OSC Messages

### Using Pure Data or Max/MSP

```
# Mute your audio
/MainMuteButton 1

# Unmute your audio
/MainMuteButton 0

# Set output gain to specific level
/OutGainSlider -6.0

# Enable metronome
/MetEnableButton 1

# Set metronome tempo to 120 BPM
/MetTempoSlider 120.0

# Start recording
/RecordingButton 1

# Push to talk (press)
/MainPushToTalkButton 1

# Push to talk (release)
/MainPushToTalkButton 0

# Reset jitter buffers
/BufferMinButton 1

# Enable stealth recording
/OptionsRecStealth 1

# Set default format to specific codec
/OptionsFormatChoiceDefaultChoice 4
```

### Using Python with python-osc

```python
from pythonosc import udp_client

# Create OSC client
client = udp_client.SimpleUDPClient("127.0.0.1", 9001)

# Mute sending
client.send_message("/MainMuteButton", 1)

# Set output level
client.send_message("/OutGainSlider", -3.0)

# Enable metronome
client.send_message("/MetEnableButton", 1)

# Set tempo
client.send_message("/MetTempoSlider", 120.0)

# Start recording
client.send_message("/RecordingButton", 1)
```

### Using TouchOSC

Create controls with the following OSC addresses:
- Toggle button with address `/MainMuteButton` sending 0/1
- Fader with address `/OutGainSlider` sending float values
- Button with address `/RecordingButton` sending 0/1
- XY Pad with `/MetTempoSlider` on one axis

## Receiving OSC Messages from SonoBus

When controls change in SonoBus (either by UI interaction or incoming OSC), the application sends OSC messages with the new values to the configured target IP and port. This allows external controllers to stay synchronized with the application state.

Example listening in Python:
```python
from pythonosc import dispatcher
from pythonosc import osc_server

def handle_mute(unused_addr, value):
    print(f"Mute state changed to: {value}")

def handle_slider(unused_addr, value):
    print(f"Slider value changed to: {value}")

# Create dispatcher
disp = dispatcher.Dispatcher()
disp.map("/MainMuteButton", handle_mute)
disp.map("/OutGainSlider", handle_slider)

# Create server
server = osc_server.ThreadingOSCUDPServer(("127.0.0.1", 9000), disp)
print("Listening for OSC messages...")
server.serve_forever()
```

## Notes

- All OSC communication is done over UDP
- Messages are sent only when OSC is enabled in the Options tab
- Float values are sent as OSC float32
- Integer values are sent as OSC int32
- Changes to parameters via OSC will trigger the same behavior as UI interaction
- Some controls may have range limits enforced by the application

## Troubleshooting

1. **Not receiving messages**: Check that the receive port matches your sender's target port
2. **Not sending messages**: Verify OSC is enabled and target IP/port are correct
3. **Values not applying**: Ensure data types match (float vs int) and values are in valid range
4. **Network issues**: If using remote control, ensure firewall allows UDP traffic on OSC ports

## Related Resources

- [OSC Specification](http://opensoundcontrol.org/spec-1_0)
- [TouchOSC](https://hexler.net/products/touchosc)
- [python-osc](https://github.com/attwad/python-osc)
