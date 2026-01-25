# SonoBus OSC Control Layout

This directory contains TouchOSC layout files and OSC control documentation for the SonoBus application.

## Files

### sonobus_comprehensive.tosc

A **TouchOSC layout file** (zlib-compressed XML) that can be directly imported into the TouchOSC editor. This file provides:

- **Comprehensive Layout**: 154 controls covering global and Input Groups 1-4
- **Visual UI Elements**: All controls have visible text labels for runtime identification
- **Ready to Configure**: Import into TouchOSC and configure OSC addresses via the editor
- **Organized**: Controls grouped by function with section headers

**Controls included (154 total):**

**Global Controls (5):**
- **OutGain** (Fader, label: "OutGain") → `/OutGainSlider`
- **MainMute** (Button, label: "MainMute") → `/MainMuteButton`
- **RecvSync** (Button, label: "RecvSync") → `/RecvSyncButton`
- **MaxRecvPad** (Fader, label: "RecvPad") → `/OptionsMaxRecvPaddingSlider`
- **RecStealth** (Button, label: "RecStealth") → `/OptionsRecStealth`

**Input Groups 1-4 (149 controls total):**

Each of the 4 groups includes 37 controls:
- **Basic Controls (8)**: Mute, Solo, Gain, Pan, InvPol, Monitor, InRev, MonRev
- **Compressor (7)**: Enable, Threshold, Ratio, Attack, Release, Makeup Gain, Auto Makeup
- **Parametric EQ (11)**: Enable, Low Shelf (Gain, Freq), Para1 (Gain, Freq, Q), Para2 (Gain, Freq, Q), High Shelf (Gain, Freq)
- **Limiter (5)**: Enable, Threshold, Ratio, Attack, Release
- **Monitor Delay (2)**: Enable, Delay Time
- **Section Labels (4)**: Group header, Compressor, EQ, Lim/Dly

**Total: 5 global + (37 × 4 groups) + 1 global label = 154 controls**

**Example Control Names with Labels:**
- G1_Gain (label: "Gain") → `/InputGroup1/Gain`
- G1_Comp_Thr (label: "Thr") → `/InputGroup1/Compressor/ThresholdDb`
- G2_EQ_P1G (label: "P1G") → `/InputGroup2/EQ/Para1Gain`
- G3_Lim_En (label: "Lim") → `/InputGroup3/Limiter/Enabled`

**Key Features:**
- All faders and buttons display text labels at runtime
- Compact layout fits 1280×960 display
- Color-coded by function (blue=levels, red=mute/threshold, green=monitoring, etc.)
- Groups 5-16 can be added by duplicating Group 1-4 patterns in TouchOSC editor

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

**Note**: 
- The .tosc file is a zlib-compressed XML layout
- TouchOSC v2.x will handle this format automatically
- OSC addresses must be configured manually in the TouchOSC editor (the layout only includes visual controls)
- The layout includes 154 controls covering global settings and Input Groups 1-4
- All controls display text labels at runtime for easy identification

### With Other OSC Controllers

The OSC address structure is documented in `sonobus_osc_reference.json` and can be used with any OSC-capable controller:

- **Open Sound Control (OSC)** protocol support required
- Send messages to the appropriate addresses as documented
- Respect the data types (int for toggles, float for continuous values)
- Use the documented value ranges for best results

### Extending the Layout

The provided .tosc file includes 154 controls covering global settings and complete parameters for Input Groups 1-4. To add Input Groups 5-16:

1. Open `sonobus_comprehensive.tosc` in TouchOSC editor
2. Select all controls for one group (e.g., Group 1)
3. Duplicate and reposition for the new group
4. Rename controls (e.g., G1_Gain → G5_Gain)
5. Update OSC addresses (e.g., `/InputGroup1/Gain` → `/InputGroup5/Gain`)
6. Save and export the modified layout

The pattern is consistent across all groups, making duplication straightforward.

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

The `sonobus_comprehensive.tosc` file includes **154 controls** organized in sections:
- **5 Global controls**: Output gain, mute, sync, padding, stealth
- **4 Complete Input Groups (37 controls each)**:
  - 8 Basic controls per group: Mute, solo, gain, pan, polarity, monitor, reverb sends
  - 7 Compressor parameters: Enable, threshold, ratio, attack, release, makeup gain, auto
  - 11 EQ parameters: Enable, 4-band EQ (low shelf, 2 parametric, high shelf) with gain/freq/Q
  - 5 Limiter parameters: Enable, threshold, ratio, attack, release
  - 2 Monitor Delay parameters: Enable, delay time
  - 4 Section labels per group: Group header, Compressor, EQ, Lim/Dly

**Runtime Visibility**:
- All faders and buttons display text labels for easy identification
- Labels are visible directly on controls in TouchOSC
- No need to check property panels to identify controls

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

1. Open `sonobus_comprehensive.tosc` in TouchOSC editor
2. Make changes using the visual editor
3. Export and save the modified layout
4. Test with TouchOSC or OSC testing tools
5. Document any new controls or changes

Note: The .tosc file is zlib-compressed XML, not JSON. Use TouchOSC editor or decompress with Python for manual editing.

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
