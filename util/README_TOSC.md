# SonoBus OSC Control Layout

This directory contains TouchOSC layout files and OSC control documentation for the SonoBus application.

## Files

### sonobus_comprehensive.tosc

A **TouchOSC layout file** (ZIP archive containing XML) that can be directly imported into the TouchOSC editor. This file provides:

- **Tab-based Layout**: Organized sections for different control categories
- **Visual UI Elements**: Faders, toggles, rotaries, and labels
- **Pre-configured OSC Addresses**: All controls are mapped to SonoBus OSC commands
- **Ready to Use**: Import directly into TouchOSC desktop or mobile apps

### sonobus_osc_reference.json

A **comprehensive JSON reference document** that lists all OSC control addresses available in SonoBus:

- **Global Controls**: Output gain, main mute, receive sync, and configuration options
- **Input Group Controls**: Support for Input Groups 1-16 with full parameter control
- **Complete Documentation**: All 933 OSC addresses with data types and ranges
- **Implementation Notes**: Guidance for extending and customizing controls

## OSC Address Structure

### Global Controls

All global controls use simple root-level addresses:

```
/OutGainSlider                      - Output gain (float, 0.0-1.0)
/MainMuteButton                     - Main mute (int, 0 or 1)
/RecvSyncButton                     - Receive sync (int, 0 or 1)
/OptionsMaxRecvPaddingSlider        - Max receive padding (float, 0.0-1.0)
/OptionsRecStealth                  - Recording stealth mode (int, 0 or 1)
```

### Input Group Controls

Input group controls follow a hierarchical pattern: `/InputGroupN/<Category>/<Parameter>`

Where `N` is the group number (1-16).

#### Basic Controls

```
/InputGroupN/Mute                   - Mute toggle (int, 0 or 1)
/InputGroupN/Solo                   - Solo toggle (int, 0 or 1)
/InputGroupN/Gain                   - Input gain (float, 0.0-2.0)
/InputGroupN/Pan                    - Pan position (float, -1.0 to 1.0)
/InputGroupN/InvertPolarity         - Polarity invert (int, 0 or 1)
/InputGroupN/Monitor                - Monitor level (float, 0.0-1.0)
/InputGroupN/InReverbSend           - Input reverb send (float, 0.0-1.0)
/InputGroupN/MonReverbSend          - Monitor reverb send (float, 0.0-1.0)
```

#### Compressor

```
/InputGroupN/Compressor/Enabled         - Enable (int, 0 or 1)
/InputGroupN/Compressor/ThresholdDb     - Threshold (float, -60.0 to 0.0 dB)
/InputGroupN/Compressor/Ratio           - Ratio (float, 1.0-20.0)
/InputGroupN/Compressor/AttackMs        - Attack (float, 0.1-100.0 ms)
/InputGroupN/Compressor/ReleaseMs       - Release (float, 10.0-1000.0 ms)
/InputGroupN/Compressor/MakeupGainDb    - Makeup gain (float, 0.0-24.0 dB)
/InputGroupN/Compressor/AutomakeupGain  - Auto makeup (int, 0 or 1)
```

#### Expander/Gate

```
/InputGroupN/Expander/Enabled           - Enable (int, 0 or 1)
/InputGroupN/Expander/ThresholdDb       - Threshold (float, -60.0 to 0.0 dB)
/InputGroupN/Expander/Ratio             - Ratio (float, 1.0-20.0)
/InputGroupN/Expander/AttackMs          - Attack (float, 0.1-100.0 ms)
/InputGroupN/Expander/ReleaseMs         - Release (float, 10.0-1000.0 ms)
/InputGroupN/Expander/MakeupGainDb      - Makeup gain (float, 0.0-24.0 dB)
/InputGroupN/Expander/AutomakeupGain    - Auto makeup (int, 0 or 1)
```

#### Parametric EQ (4-band)

```
/InputGroupN/EQ/Enabled                 - Enable (int, 0 or 1)
/InputGroupN/EQ/LowShelfGain            - Low shelf gain (float, -12.0 to 12.0 dB)
/InputGroupN/EQ/LowShelfFreq            - Low shelf freq (float, 20.0-500.0 Hz)
/InputGroupN/EQ/Para1Gain               - Para 1 gain (float, -12.0 to 12.0 dB)
/InputGroupN/EQ/Para1Freq               - Para 1 freq (float, 20.0-20000.0 Hz)
/InputGroupN/EQ/Para1Q                  - Para 1 Q (float, 0.1-10.0)
/InputGroupN/EQ/Para2Gain               - Para 2 gain (float, -12.0 to 12.0 dB)
/InputGroupN/EQ/Para2Freq               - Para 2 freq (float, 20.0-20000.0 Hz)
/InputGroupN/EQ/Para2Q                  - Para 2 Q (float, 0.1-10.0)
/InputGroupN/EQ/HighShelfGain           - High shelf gain (float, -12.0 to 12.0 dB)
/InputGroupN/EQ/HighShelfFreq           - High shelf freq (float, 1000.0-20000.0 Hz)
```

#### Limiter

```
/InputGroupN/Limiter/Enabled            - Enable (int, 0 or 1)
/InputGroupN/Limiter/ThresholdDb        - Threshold (float, -60.0 to 0.0 dB)
/InputGroupN/Limiter/Ratio              - Ratio (float, 10.0-100.0)
/InputGroupN/Limiter/AttackMs           - Attack (float, 0.01-10.0 ms)
/InputGroupN/Limiter/ReleaseMs          - Release (float, 10.0-1000.0 ms)
```

#### Monitor Delay

```
/InputGroupN/MonitorDelay/Enabled       - Enable (int, 0 or 1)
/InputGroupN/MonitorDelay/DelayTimeMs   - Delay time (float, 0.0-1000.0 ms)
```

## Usage

### With TouchOSC

1. Open TouchOSC application (desktop or mobile)
2. Import the `sonobus_comprehensive.tosc` file:
   - **Desktop**: File → Open, select the .tosc file
   - **Mobile**: Transfer via iTunes/Files and import in app
3. Configure OSC connection settings to point to SonoBus:
   - Host: IP address of machine running SonoBus
   - Port: OSC receive port configured in SonoBus (typically 9000-9999)
4. Enable OSC in SonoBus settings
5. Use the visual controls to send OSC messages to SonoBus

**Note**: The .tosc file is a ZIP archive containing XML layout definitions. TouchOSC will handle this format automatically.

### With Other OSC Controllers

The OSC address structure is documented in `sonobus_osc_reference.json` and can be used with any OSC-capable controller:

- **Open Sound Control (OSC)** protocol support required
- Send messages to the appropriate addresses as documented
- Respect the data types (int for toggles, float for continuous values)
- Use the documented value ranges for best results

### Extending the Layout

The provided .tosc file includes controls for:
- **Global Controls**: All 5 global parameters
- **Input Group 1**: Basic controls, compressor, and EQ tabs

To add controls for Input Groups 2-16:

1. Open `sonobus_comprehensive.tosc` in TouchOSC editor
2. Duplicate existing tabs (Global, Group 1, G1 Comp, G1 EQ)
3. Update the group number in OSC addresses (e.g., `/InputGroup2/...`)
4. Adjust tab names and labels
5. Save and export the modified layout

**Alternatively**, manually edit the XML:
1. Extract the .tosc file: `unzip sonobus_comprehensive.tosc`
2. Edit `index.xml` to add more tabpages and controls
3. Re-zip: `zip sonobus_comprehensive.tosc index.xml`

## Examples

### Setting Input Group 1 Gain to 75%

```
OSC Message: /InputGroup1/Gain
Value: 0.75 (float)
```

### Enabling Compressor on Input Group 3

```
OSC Message: /InputGroup3/Compressor/Enabled
Value: 1 (int)
```

### Adjusting EQ Low Shelf on Input Group 5

```
OSC Message: /InputGroup5/EQ/LowShelfGain
Value: 3.5 (float, represents +3.5dB)
```

## Technical Details

### .tosc File Format

The `sonobus_comprehensive.tosc` file is a **ZIP archive** containing XML layout definitions, which is the standard format for TouchOSC v1.x (Mk1) layouts. This format:

- **Container**: ZIP archive with `.tosc` extension
- **Contents**: `index.xml` file with TouchOSC layout definition
- **Compatibility**: TouchOSC v1.x and v2.x (legacy mode)
- **Editing**: Can be opened in TouchOSC editor or manually by extracting ZIP

To inspect the contents:
```bash
unzip -l sonobus_comprehensive.tosc
```

To extract and view the XML:
```bash
unzip sonobus_comprehensive.tosc
cat index.xml
```

### Data Types

- **int**: Integer values, typically 0 or 1 for toggles
- **float**: Floating-point values for continuous parameters

### Value Ranges

All value ranges are documented in the OSC address reference. These ranges are based on:

- SonoBus source code analysis (ChannelGroupParams structure)
- Audio DSP best practices
- Typical parameter ranges for audio effects

### Implementation Status

**Currently Registered in SonoBus Code** (as of analysis):
- `/OutGainSlider`
- `/MainMuteButton`
- `/RecvSyncButton`
- `/OptionsMaxRecvPaddingSlider`
- `/OptionsRecStealth`

**Proposed (Input Group Controls)**:
- All Input Group addresses are defined in this layout
- Implementation in SonoBus code may be required for full functionality
- Refer to `Source/SonobusPluginEditor.cpp` for registering new controls

## Integration with SonoBus

To enable these OSC controls in SonoBus, the controls need to be registered in the code using `OSCManager::registerControl()`. See the existing implementation in:

- `Source/OSCManager.h` - OSC manager interface
- `Source/OSCManager.cpp` - OSC message handling
- `Source/SonobusPluginEditor.cpp` - Control registration examples

Example registration:

```cpp
oscManager.registerControl("/InputGroup1/Gain", [this](const juce::OSCMessage& message) {
    if (message.size() == 1 && message[0].isFloat32()) {
        float value = message[0].getFloat32();
        // Apply gain value to Input Group 1
    }
});
```

## Compatibility

- **TouchOSC**: Primary target platform
- **Other OSC Controllers**: Any application supporting OSC protocol
- **SonoBus Version**: Designed for versions with OSC support (v1.7.5+)

## Contributing

To extend or improve this layout:

1. Edit `sonobus_comprehensive.tosc` (valid JSON format)
2. Validate JSON structure: `python3 -m json.tool sonobus_comprehensive.tosc`
3. Test with TouchOSC or OSC testing tools
4. Document any new controls or changes

## License

This layout file is part of the SonoBus project and follows the same GPLv3 license.

## References

- SonoBus Project: https://sonobus.net
- TouchOSC: https://hexler.net/touchosc
- OSC Protocol: http://opensoundcontrol.org/

## Support

For questions or issues:
- SonoBus GitHub: https://github.com/sonosaurus/sonobus
- OSC Documentation: Refer to SonoBus user documentation
- TouchOSC Support: https://hexler.net/touchosc/manual
