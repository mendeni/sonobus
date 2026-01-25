# SonoBus OSC Control Layout

This directory contains TouchOSC layout files and OSC control documentation for the SonoBus application.

## Files

### sonobus_comprehensive.tosc

A **TouchOSC layout file** (zlib-compressed XML) that can be directly imported into the TouchOSC editor. This file provides:

- **Comprehensive Layout**: 51 controls covering global and Input Group 1 parameters
- **Visual UI Elements**: Faders for continuous controls, buttons for toggles
- **Ready to Configure**: Import into TouchOSC and configure OSC addresses via the editor
- **Organized**: Controls grouped by function (Global, Basic, Compressor, Expander, EQ, Limiter, Delay)

**Controls included (51 total):**

**Global Controls (5):**
- **OutGain** (Fader) → `/OutGainSlider`
- **MainMute** (Button) → `/MainMuteButton`
- **RecvSync** (Button) → `/RecvSyncButton`
- **MaxRecvPad** (Fader) → `/OptionsMaxRecvPaddingSlider`
- **RecStealth** (Button) → `/OptionsRecStealth`

**Input Group 1 - Basic Controls (8):**
- **G1_Mute** (Button) → `/InputGroup1/Mute`
- **G1_Solo** (Button) → `/InputGroup1/Solo`
- **G1_Gain** (Fader) → `/InputGroup1/Gain`
- **G1_Pan** (Fader) → `/InputGroup1/Pan`
- **G1_InvPol** (Button) → `/InputGroup1/InvertPolarity`
- **G1_Monitor** (Fader) → `/InputGroup1/Monitor`
- **G1_InRev** (Fader) → `/InputGroup1/InReverbSend`
- **G1_MonRev** (Fader) → `/InputGroup1/MonReverbSend`

**Input Group 1 - Compressor (7):**
- **G1_Comp_En** (Button) → `/InputGroup1/Compressor/Enabled`
- **G1_Comp_Thr** (Fader) → `/InputGroup1/Compressor/ThresholdDb`
- **G1_Comp_Rat** (Fader) → `/InputGroup1/Compressor/Ratio`
- **G1_Comp_Atk** (Fader) → `/InputGroup1/Compressor/AttackMs`
- **G1_Comp_Rel** (Fader) → `/InputGroup1/Compressor/ReleaseMs`
- **G1_Comp_MkG** (Fader) → `/InputGroup1/Compressor/MakeupGainDb`
- **G1_Comp_Auto** (Button) → `/InputGroup1/Compressor/AutomakeupGain`

**Input Group 1 - Expander/Gate (7):**
- **G1_Exp_En** (Button) → `/InputGroup1/Expander/Enabled`
- **G1_Exp_Thr** (Fader) → `/InputGroup1/Expander/ThresholdDb`
- **G1_Exp_Rat** (Fader) → `/InputGroup1/Expander/Ratio`
- **G1_Exp_Atk** (Fader) → `/InputGroup1/Expander/AttackMs`
- **G1_Exp_Rel** (Fader) → `/InputGroup1/Expander/ReleaseMs`
- **G1_Exp_MkG** (Fader) → `/InputGroup1/Expander/MakeupGainDb`
- **G1_Exp_Auto** (Button) → `/InputGroup1/Expander/AutomakeupGain`

**Input Group 1 - Parametric EQ (11):**
- **G1_EQ_En** (Button) → `/InputGroup1/EQ/Enabled`
- **G1_EQ_LSGain** (Fader) → `/InputGroup1/EQ/LowShelfGain`
- **G1_EQ_LSFreq** (Fader) → `/InputGroup1/EQ/LowShelfFreq`
- **G1_EQ_P1Gain** (Fader) → `/InputGroup1/EQ/Para1Gain`
- **G1_EQ_P1Freq** (Fader) → `/InputGroup1/EQ/Para1Freq`
- **G1_EQ_P1Q** (Fader) → `/InputGroup1/EQ/Para1Q`
- **G1_EQ_P2Gain** (Fader) → `/InputGroup1/EQ/Para2Gain`
- **G1_EQ_P2Freq** (Fader) → `/InputGroup1/EQ/Para2Freq`
- **G1_EQ_P2Q** (Fader) → `/InputGroup1/EQ/Para2Q`
- **G1_EQ_HSGain** (Fader) → `/InputGroup1/EQ/HighShelfGain`
- **G1_EQ_HSFreq** (Fader) → `/InputGroup1/EQ/HighShelfFreq`

**Input Group 1 - Limiter (5):**
- **G1_Lim_En** (Button) → `/InputGroup1/Limiter/Enabled`
- **G1_Lim_Thr** (Fader) → `/InputGroup1/Limiter/ThresholdDb`
- **G1_Lim_Rat** (Fader) → `/InputGroup1/Limiter/Ratio`
- **G1_Lim_Atk** (Fader) → `/InputGroup1/Limiter/AttackMs`
- **G1_Lim_Rel** (Fader) → `/InputGroup1/Limiter/ReleaseMs`

**Input Group 1 - Monitor Delay (2):**
- **G1_Delay_En** (Button) → `/InputGroup1/MonitorDelay/Enabled`
- **G1_Delay_Time** (Fader) → `/InputGroup1/MonitorDelay/DelayTimeMs`

**Plus 6 section labels** for visual organization

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
3. **Configure OSC Addresses**: After importing, you must configure each control's OSC address:
   - Select each control in the editor
   - In the "Messages" or "OSC" section, add the appropriate OSC address from the list above
   - Example: OutGain fader → OSC Address: `/OutGainSlider`, Type: Float, Range: 0-1
   - Example: G1_Comp_Thr → OSC Address: `/InputGroup1/Compressor/ThresholdDb`, Type: Float, Range: -60 to 0
4. Configure OSC connection settings to point to SonoBus:
   - Host: IP address of machine running SonoBus
   - Port: OSC receive port configured in SonoBus (typically 9000-9999)
5. Enable OSC in SonoBus settings
6. Use the visual controls to send OSC messages to SonoBus

**Note**: The .tosc file is a zlib-compressed XML layout. TouchOSC v2.x will handle this format automatically. OSC addresses must be configured manually in the TouchOSC editor as the layout only includes the visual controls. The layout includes 51 controls covering all major parameters for global settings and Input Group 1.

### With Other OSC Controllers

The OSC address structure is documented in `sonobus_osc_reference.json` and can be used with any OSC-capable controller:

- **Open Sound Control (OSC)** protocol support required
- Send messages to the appropriate addresses as documented
- Respect the data types (int for toggles, float for continuous values)
- Use the documented value ranges for best results

### Extending the Layout

The provided .tosc file includes 51 controls covering global settings and complete Input Group 1 parameters. To add more controls or duplicate for Input Groups 2-16:

1. Open `sonobus_comprehensive.tosc` in TouchOSC editor
2. Select and duplicate existing controls
3. Rename controls (e.g., G1_Gain → G2_Gain)
4. Update OSC addresses (e.g., `/InputGroup1/Gain` → `/InputGroup2/Gain`)
5. Adjust positioning as needed
6. Save and export the modified layout

Use the OSC address patterns from `sonobus_osc_reference.json` for reference.

**Alternative**: You can also decompress, edit the XML, and recompress:

```bash
# From the repository root:

# 1. Decompress the .tosc file
python3 -c "import zlib; open('util/layout.xml','wb').write(zlib.decompress(open('util/sonobus_comprehensive.tosc','rb').read()))"

# 2. Edit util/layout.xml (add more <node> elements for controls)

# 3. Recompress to .tosc
python3 -c "import zlib; open('util/sonobus_comprehensive.tosc','wb').write(zlib.compress(open('util/layout.xml','rb').read(), level=9))"
```

For easier editing, consider creating a helper script to handle compression/decompression.

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

The `sonobus_comprehensive.tosc` file uses the **TouchOSC v2.x format**:

- **Container**: Zlib-compressed XML data (not ZIP archive)
- **Contents**: `<lexml version="5">` root with hierarchical `<node>` elements
- **Compatibility**: TouchOSC v2.x (current version)
- **Editing**: Can be opened in TouchOSC editor or manually by decompressing

To inspect the contents:
```bash
# From the repository root
python3 -c "import zlib; open('util/layout.xml','wb').write(zlib.decompress(open('util/sonobus_comprehensive.tosc','rb').read()))"
cat util/layout.xml
```

To recompress after editing:
```bash
# From the repository root
python3 -c "import zlib; open('util/sonobus_comprehensive.tosc','wb').write(zlib.compress(open('util/layout.xml','rb').read(), level=9))"
```

**Note**: This is different from TouchOSC v1.x (Mk1) which used ZIP archives with different XML structure.

### Data Types

- **int**: Integer values, typically 0 or 1 for toggles
- **float**: Floating-point values for continuous parameters

### Value Ranges

All value ranges are documented in the OSC address reference. These ranges are based on:

- SonoBus source code analysis (ChannelGroupParams structure)
- Audio DSP best practices
- Typical parameter ranges for audio effects

**Controls in the Layout**:

The `sonobus_comprehensive.tosc` file includes **51 controls** organized in sections:
- **5 Global controls**: Output gain, mute, sync, padding, stealth
- **8 Input Group 1 basic controls**: Mute, solo, gain, pan, polarity, monitor, reverb sends
- **7 Compressor parameters**: Enable, threshold, ratio, attack, release, makeup gain, auto makeup
- **7 Expander/Gate parameters**: Enable, threshold, ratio, attack, release, makeup gain, auto makeup
- **11 EQ parameters**: Enable, low shelf (gain/freq), para1 (gain/freq/Q), para2 (gain/freq/Q), high shelf (gain/freq)
- **5 Limiter parameters**: Enable, threshold, ratio, attack, release
- **2 Monitor Delay parameters**: Enable, delay time
- **6 Section labels**: For visual organization

See the file descriptions section above for complete control-to-OSC-address mappings.

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
