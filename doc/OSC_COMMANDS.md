# SonoBus OSC Command Reference

This document provides a comprehensive reference for controlling SonoBus via Open Sound Control (OSC).

## Overview

SonoBus supports OSC for remote control and automation. OSC messages can control most parameters in SonoBus, enabling integration with controllers, DAWs, and other OSC-enabled software.

## Configuration

### Enable OSC
1. Open SonoBus Options
2. Navigate to the Options tab
3. Enable "Enable OSC Control"
4. Configure ports and host as needed

### Default Settings
- **Receive Port**: 9951 (incoming OSC messages)
- **Send Host**: 127.0.0.1 (where feedback is sent)
- **Send Port**: 9952 (outgoing OSC feedback)

## OSC Address Namespace

All SonoBus OSC messages use the namespace: `/sonobus/`

## Supported Parameters

### Audio Controls

| OSC Address | Type | Range | Description |
|------------|------|-------|-------------|
| `/sonobus/ingain` | float | 0.0 - 4.0 | Input gain level |
| `/sonobus/dry` | float | 0.0 - 1.0 | Dry (monitor) level |
| `/sonobus/wet` | float | 0.0 - 2.0 | Output (wet) level |
| `/sonobus/inmonmonopan` | float | -1.0 - 1.0 | Input mono pan (-1=left, 0=center, 1=right) |
| `/sonobus/inmonpan1` | float | -1.0 - 1.0 | Input channel 1 pan |
| `/sonobus/inmonpan2` | float | -1.0 - 1.0 | Input channel 2 pan |

### Metronome Controls

| OSC Address | Type | Range | Description |
|------------|------|-------|-------------|
| `/sonobus/metenabled` | int/float | 0 or 1 | Enable/disable metronome |
| `/sonobus/metgain` | float | 0.0 - 1.0 | Metronome volume |
| `/sonobus/mettempo` | float | 10.0 - 400.0 | Metronome tempo (BPM) |
| `/sonobus/sendmetaudio` | int/float | 0 or 1 | Send metronome to others |
| `/sonobus/metisrecorded` | int/float | 0 or 1 | Record metronome to file |
| `/sonobus/syncMetHost` | int/float | 0 or 1 | Sync metronome to host (plugin mode) |
| `/sonobus/syncMetFile` | int/float | 0 or 1 | Sync metronome to file playback |

### Main Bus Controls

| OSC Address | Type | Range | Description |
|------------|------|-------|-------------|
| `/sonobus/mastsendmute` | int/float | 0 or 1 | Mute all send |
| `/sonobus/mastrecvmute` | int/float | 0 or 1 | Mute all receive |
| `/sonobus/mastinmute` | int/float | 0 or 1 | Mute input monitor |
| `/sonobus/mastmonsolo` | int/float | 0 or 1 | Solo monitoring |

### Reverb Controls

| OSC Address | Type | Range | Description |
|------------|------|-------|-------------|
| `/sonobus/mainreverbenabled` | int/float | 0 or 1 | Enable main reverb |
| `/sonobus/nmainreverblevel` | float | 0.0 - 1.0 | Main reverb level |
| `/sonobus/mainreverbsize` | float | 0.0 - 1.0 | Main reverb size |
| `/sonobus/mainreverbdamp` | float | 0.0 - 1.0 | Main reverb damping |
| `/sonobus/mainreverbpredelay` | float | 0.0 - 100.0 | Main reverb pre-delay (ms) |
| `/sonobus/mainreverbmodel` | int | 0, 1, 2 | Reverb model (0=Freeverb, 1=MVerb, 2=Zita) |
| `/sonobus/inreverblevel` | float | 0.0 - 1.0 | Input reverb level |
| `/sonobus/inreverbsize` | float | 0.0 - 1.0 | Input reverb size |
| `/sonobus/inreverbdamp` | float | 0.0 - 1.0 | Input reverb damping |
| `/sonobus/inreverbpredelay` | float | 0.0 - 100.0 | Input reverb pre-delay (ms) |

### File Playback

| OSC Address | Type | Range | Description |
|------------|------|-------|-------------|
| `/sonobus/sendfileaudio` | int/float | 0 or 1 | Send file playback audio |

### Soundboard

| OSC Address | Type | Range | Description |
|------------|------|-------|-------------|
| `/sonobus/sendsoundboardaudio` | int/float | 0 or 1 | Send soundboard audio |

### Network/Buffer Settings

| OSC Address | Type | Range | Description |
|------------|------|-------|-------------|
| `/sonobus/buffertime` | float | 0.0 - varies | Jitter buffer time (seconds) |
| `/sonobus/defnetbuf` | float | 0.0 - varies | Default network buffer (seconds) |
| `/sonobus/defnetauto` | int | 0-3 | Auto buffer mode (0=Off, 1=Auto-Increase, 2=Auto-Full, 3=Initial-Auto) |
| `/sonobus/defsendqual` | int | 0-14 | Default send quality format |
| `/sonobus/dynamicresampling` | int/float | 0 or 1 | Enable dynamic resampling |

### Other Controls

| OSC Address | Type | Range | Description |
|------------|------|-------|-------------|
| `/sonobus/sendchannels` | int | 0, 1, 2 | Send channels (0=Match Inputs, 1=Mono, 2=Stereo) |
| `/sonobus/hearlatencytest` | int/float | 0 or 1 | Hear latency test audio |
| `/sonobus/reconnectlast` | int/float | 0 or 1 | Auto-reconnect to last group |
| `/sonobus/defPeerLevel` | float | 0.0 - 1.0 | Default peer level |

## Feedback Messages

When SonoBus receives a valid OSC message and updates a parameter, it sends a feedback message:

```
/sonobus/<parameter>/feedback <value>
```

Example:
```
# Send: /sonobus/ingain 0.75
# Receive: /sonobus/ingain/feedback 0.75
```

## Testing and Debugging

### Ping/Pong
Test OSC connectivity:
```
# Send: /sonobus/ping
# Receive: /sonobus/pong "SonoBus OSC"
```

### Using oscsend (Linux/Mac)
```bash
# Install liblo-tools
# Ubuntu/Debian: sudo apt-get install liblo-tools
# Mac: brew install liblo

# Send a message
oscsend localhost 9951 /sonobus/ingain f 0.8

# Test ping
oscsend localhost 9951 /sonobus/ping
```

### Using osculator or similar tools
Most OSC testing tools can be configured to send/receive on the appropriate ports.

## Example Scripts

### Python Example
```python
from pythonosc import udp_client, dispatcher, osc_server
import threading

# Create OSC client to send to SonoBus
client = udp_client.SimpleUDPClient("127.0.0.1", 9951)

# Send some commands
client.send_message("/sonobus/ingain", 0.75)
client.send_message("/sonobus/metenabled", 1)
client.send_message("/sonobus/mettempo", 120.0)

# Create server to receive feedback
def feedback_handler(address, *args):
    print(f"Received: {address} {args}")

dispatcher = dispatcher.Dispatcher()
dispatcher.map("/sonobus/*", feedback_handler)

server = osc_server.ThreadingOSCUDPServer(("127.0.0.1", 9952), dispatcher)
server_thread = threading.Thread(target=server.serve_forever)
server_thread.daemon = True
server_thread.start()
```

### Max/MSP Example
```
// Send to SonoBus
[prepend /sonobus/ingain]
|
[udpsend 127.0.0.1 9951]

// Receive feedback from SonoBus
[udpreceive 9952]
|
[route /sonobus]
|
[print feedback]
```

### Pure Data Example
```
[/sonobus/ingain 0.75(
|
[send localhost:9951]

[netreceive 9952]
|
[route /sonobus]
|
[print]
```

## Notes

- All float values should be sent as OSC float type (32-bit)
- Boolean parameters (0/1) accept both int and float types
- Parameter names are case-sensitive
- Unknown parameters are ignored
- Invalid parameter values may be clamped to valid ranges
- OSC communication uses UDP, so messages are not guaranteed to arrive
- State is automatically saved when OSC settings change
- OSC works in both standalone and plugin versions of SonoBus

## Troubleshooting

1. **No response from SonoBus**
   - Verify OSC is enabled in Options
   - Check firewall settings
   - Ensure correct IP address and port
   - Try sending a `/sonobus/ping` message

2. **Parameters not changing**
   - Verify parameter name is correct (case-sensitive)
   - Check value is in valid range
   - Ensure value type is correct (float vs int)

3. **Not receiving feedback**
   - Verify Send Host and Send Port in Options
   - Check receiving application is listening on correct port
   - Ensure firewall allows outgoing UDP on the send port

## Advanced Usage

### Controlling Multiple Instances
If running multiple SonoBus instances, use different receive ports for each:
- Instance 1: Port 9951
- Instance 2: Port 9953
- Instance 3: Port 9955

### Integration with DAWs
When using SonoBus as a plugin in a DAW, OSC control is still available. This allows external controllers to manipulate SonoBus parameters independently of the DAW's automation.

### Network Control
OSC can operate over networks. Set the Send Host to the IP of a remote computer to send feedback to external controllers on your network.
