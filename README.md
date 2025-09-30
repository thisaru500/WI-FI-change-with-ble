# WiFi Configuration with Bluetooth (ESP32)

A simple ESP32 project that allows WiFi configuration via Bluetooth Low Energy (BLE). This project enables users to configure WiFi credentials wirelessly without needing physical access to the device or a serial connection.

## Features

- 🔗 **Bluetooth Configuration**: Set WiFi credentials via Bluetooth
- 💾 **Persistent Storage**: WiFi credentials saved in non-volatile memory
- 🔄 **Auto-Reconnection**: Automatically reconnects to WiFi after reset
- 📊 **Status Monitoring**: Real-time WiFi status, IP address, and signal strength
- 🧹 **Credential Management**: Easy clearing of saved credentials
- 📱 **Cross-Platform**: Works with any Bluetooth-enabled device

## Hardware Requirements

- ESP32 development board
- USB cable for programming and power

## Software Requirements

- Arduino IDE with ESP32 board support
- Bluetooth terminal app (for mobile devices) or serial terminal

## Installation

1. **Clone this repository**
   ```bash
   git clone https://github.com/yourusername/WI-FI-change-with-ble.git
   cd WI-FI-change-with-ble
   ```

2. **Install ESP32 Board Support**
   - Open Arduino IDE
   - Go to File → Preferences
   - Add this URL to "Additional Board Manager URLs":
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Go to Tools → Board → Boards Manager
   - Search for "ESP32" and install "ESP32 by Espressif Systems"

3. **Install Required Libraries**
   - The code uses built-in ESP32 libraries (BluetoothSerial, WiFi, Preferences)
   - No additional libraries required

4. **Upload the Code**
   - Open `arduino_code/arduino_code.ino` in Arduino IDE
   - Select your ESP32 board (Tools → Board → ESP32 Arduino → your board)
   - Select the correct COM port
   - Click Upload

## Usage

### Initial Setup

1. **Power on the ESP32** - The device will start with Bluetooth name "TDD access point"
2. **Connect via Bluetooth** using a Bluetooth terminal app on your phone/computer
3. **Send configuration commands** as described below

### Available Commands

| Command               | Description                             | Example              |
| --------------------- | --------------------------------------- | -------------------- |
| `SSID:<network_name>` | Set the Wi-Fi network name              | `SSID:MyHomeWiFi`    |
| `PASS:<password>`     | Set the Wi-Fi password                  | `PASS:mypassword123` |
| `CONNECT`             | Connect to the configured Wi-Fi network | `CONNECT`            |
| `STATUS`              | Check the current connection status     | `STATUS`             |
| `CLEAR`               | Clear saved Wi-Fi credentials           | `CLEAR`              |


### Step-by-Step Configuration

1. **Set WiFi Network Name**
   ```
   SSID:YourWiFiNetwork
   ```

2. **Set WiFi Password**
   ```
   PASS:YourWiFiPassword
   ```

3. **Connect to WiFi**
   ```
   CONNECT
   ```

4. **Check Status**
   ```
   STATUS
   ```

### Example Session

```
ESP32 WiFi Configuration
Commands:
  SSID:<your_ssid>
  PASS:<your_password>
  CONNECT
  STATUS
  CLEAR

SSID:MyHomeNetwork
SSID saved: MyHomeNetwork

PASS:MySecurePassword
Password saved: 14 characters

CONNECT
Attempting to connect to WiFi...
.....
WiFi Connected!
IP Address: 192.168.1.100

STATUS
--- WiFi Status ---
SSID: MyHomeNetwork
Password: Set (14 chars)
Connection: Connected
IP Address: 192.168.1.100
Signal Strength: -45 dBm
-------------------
```

## Project Structure

```
WI-FI-change-with-ble/
├── arduino_code/
│   └── arduino_code.ino    # Main ESP32 code
├── Working_Photoes/        # Screenshots and documentation images
├── LICENSE                 # Project license
└── README.md              # This file
```

## How It Works

1. **Bluetooth Communication**: The ESP32 creates a Bluetooth serial connection for receiving commands
2. **Credential Storage**: WiFi credentials are stored in ESP32's non-volatile memory using Preferences library
3. **Auto-Reconnection**: On startup, the device automatically attempts to connect using saved credentials
4. **Status Monitoring**: Continuous monitoring of WiFi connection status with real-time updates

## Troubleshooting

### Common Issues

- **Bluetooth not connecting**: Ensure Bluetooth is enabled on your device and try pairing again
- **WiFi connection fails**: Verify SSID and password are correct, check WiFi network availability
- **Device not responding**: Check if ESP32 is properly powered and code is uploaded correctly

### Debug Information

- Open Serial Monitor (115200 baud) to see detailed debug information
- All Bluetooth commands are also logged to Serial Monitor
- Check the Working_Photoes folder for example outputs

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Built for ESP32 using Arduino framework
- Uses ESP32's built-in Bluetooth and WiFi capabilities
- Inspired by the need for wireless IoT device configuration
