# Simple OSC Layout (simple_osc.tosc)

A minimal TouchOSC layout with OSC send and receive capability for testing SonoBus OSC integration.

## Contents

This file contains 13 controls with full OSC bidirectional communication, using official OSC addresses from [OSC_COMMANDS.md](https://github.com/mendeni/sonobus/blob/copilot/extend-osc-peer-controls/doc/OSC_COMMANDS.md).

### Controls

**Global Controls:**

1. **DrySlider** (Vertical Fader)
   - Label: "DrySlider"
   - OSC Address: `/DrySlider`
   - Description: Monitor (dry) level - your own audio that you hear
   - Data Type: Float (audio level in decibels)

2. **OutGainSlider** (Vertical Fader)
   - Label: "OutGainSlider"
   - OSC Address: `/OutGainSlider`
   - Description: Output (wet) level - mix of all incoming audio
   - Data Type: Float (audio level in decibels)

3. **MainMuteButton** (Toggle Button)
   - Label: "MainMute"
   - OSC Address: `/MainMuteButton`
   - Description: Mutes/unmutes sending your audio to others
   - Data Type: Integer (0 = unmuted/sending, 1 = muted/not sending)

4. **RecvSyncButton** (Push Button)
   - Label: "RecvSync"
   - OSC Address: `/RecvSyncButton`
   - Description: Synchronizes receive latency for all users
   - Data Type: Integer (1 to trigger)

5. **MainReverbEnabled** (Toggle Button)
   - Label: "Reverb"
   - OSC Address: `/MainReverbEnabled`
   - Description: Enables/disables the main reverb effect
   - Data Type: Integer (0 = disabled, 1 = enabled)

6. **ReverbLevelSlider** (Vertical Fader)
   - Label: "Reverb Level"
   - OSC Address: `/ReverbLevelSlider`
   - Description: Controls the reverb level/mix
   - Data Type: Float (audio level)

**Input Group 1 Controls:**

7. **InputGroup1PreLevel** (Vertical Fader)
   - Label: "IG1 Gain"
   - OSC Address: `/InputGroup1PreLevel`
   - Description: Pre-fader level (gain) for Input Group 1
   - Data Type: Float

8. **InputGroup1Pan** (Horizontal Fader)
   - Label: "IG1 Pan"
   - OSC Address: `/InputGroup1Pan`
   - Description: Stereo pan position for Input Group 1
   - Data Type: Float

9. **InputGroup1Mute** (Toggle Button)
   - Label: "IG1 Mute"
   - OSC Address: `/InputGroup1Mute`
   - Description: Mute toggle for Input Group 1
   - Data Type: Integer (0 = unmuted, 1 = muted)

10. **InputGroup1Solo** (Toggle Button)
    - Label: "IG1 Solo"
    - OSC Address: `/InputGroup1Solo`
    - Description: Solo toggle for Input Group 1
    - Data Type: Integer (0 = not soloed, 1 = soloed)

11. **InputGroup1Monitor** (Vertical Fader)
    - Label: "IG1 Monitor"
    - OSC Address: `/InputGroup1Monitor`
    - Description: Monitor level for Input Group 1
    - Data Type: Float

## Features

- **Bidirectional OSC**: All controls can both send and receive OSC messages
- **Official Addresses**: Uses OSC addresses from OSC_COMMANDS.md specification
- **Compact Layout**: 600×450 pixels, suitable for testing
- **Visible Labels**: Text labels on all controls for easy identification
- **Tested Format**: TouchOSC v2.x zlib-compressed XML format

## Usage

1. Import `simple_osc.tosc` into TouchOSC editor or app
2. Configure OSC connection:
   - **Host**: IP address of machine running SonoBus
   - **Outgoing Port**: OSC receive port in SonoBus (default: 9001)
   - **Incoming Port**: Port for TouchOSC to receive updates (e.g., 9002)
3. In SonoBus, enable OSC and configure:
   - **OSC Receive Port**: Match TouchOSC outgoing port (e.g., 9001)
   - **OSC Send Host**: TouchOSC device IP
   - **OSC Send Port**: Match TouchOSC incoming port (e.g., 9002)
4. Test bidirectional communication:
   - Move controls in TouchOSC → SonoBus should respond
   - Change parameters in SonoBus → TouchOSC controls should update

## OSC Message Details

Each control has 2 OSC messages configured:

- **Send Message**: Triggered when control value changes
  - Sends control value to configured OSC address
  - Format: OSC address + float/int value

- **Receive Message**: Listens for incoming OSC messages
  - Updates control when message received on OSC address
  - Format: OSC address + float/int value

## Purpose

This file is designed for:
- Testing OSC communication with SonoBus
- Demonstrating bidirectional OSC capability
- Simple control surface for basic SonoBus parameters
- Reference for implementing OSC messaging in custom layouts

## Reference

All OSC addresses match the official specification:
- [OSC_COMMANDS.md](https://github.com/mendeni/sonobus/blob/copilot/extend-osc-peer-controls/doc/OSC_COMMANDS.md)

## Extending

To add more controls from OSC_COMMANDS.md:
1. Open in TouchOSC editor
2. Add controls (faders, buttons, etc.)
3. For each control:
   - Go to Messages panel
   - Add OSC message for sending (trigger: Value Changed)
   - Add OSC message for receiving (trigger: On Receive)
   - Set OSC address from OSC_COMMANDS.md
   - Map to control value path (/values/x)
