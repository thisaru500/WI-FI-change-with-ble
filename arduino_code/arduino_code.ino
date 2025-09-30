#include "BluetoothSerial.h"
#include <WiFi.h>
#include <Preferences.h>

BluetoothSerial SerialBT;
Preferences preferences;

String ssid = "";
String password = "";
bool wifiConnected = false;

void setup() {
  Serial.begin(115200);
  
  // Initialize Preferences
  preferences.begin("wifi-config", false);
  
  // Load saved WiFi credentials
  ssid = preferences.getString("ssid", "");
  password = preferences.getString("password", "");
  
  Serial.println("ESP32 WiFi Configuration via Bluetooth");
  
  // Start Bluetooth
  SerialBT.begin("ESP32_Config"); // Bluetooth device name
  Serial.println("Bluetooth Started! Device name: ESP32_Config");
  SerialBT.println("ESP32 WiFi Configuration");
  SerialBT.println("Commands:");
  SerialBT.println("  SSID:<your_ssid>");
  SerialBT.println("  PASS:<your_password>");
  SerialBT.println("  CONNECT");
  SerialBT.println("  STATUS");
  SerialBT.println("  CLEAR");
  
  // Try to connect with saved credentials
  if (ssid.length() > 0) {
    SerialBT.println("\nFound saved WiFi credentials. Connecting...");
    connectToWiFi();
  }
}

void loop() {
  // Check for Bluetooth commands
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n');
    command.trim();
    handleCommand(command);
  }
  
  // Monitor WiFi connection
  if (wifiConnected && WiFi.status() != WL_CONNECTED) {
    wifiConnected = false;
    SerialBT.println("WiFi disconnected!");
  }
  
  delay(100);
}

void handleCommand(String command) {
  Serial.println("Received: " + command);
  
  if (command.startsWith("SSID:")) {
    ssid = command.substring(5);
    ssid.trim();
    preferences.putString("ssid", ssid);
    SerialBT.println("SSID saved: " + ssid);
    Serial.println("SSID saved: " + ssid);
  }
  else if (command.startsWith("PASS:")) {
    password = command.substring(5);
    password.trim();
    preferences.putString("password", password);
    SerialBT.println("Password saved: " + String(password.length()) + " characters");
    Serial.println("Password saved");
  }
  else if (command == "CONNECT") {
    if (ssid.length() == 0) {
      SerialBT.println("Error: SSID not set. Use SSID:<your_ssid>");
      return;
    }
    SerialBT.println("Attempting to connect to WiFi...");
    connectToWiFi();
  }
  else if (command == "STATUS") {
    SerialBT.println("\n--- WiFi Status ---");
    SerialBT.println("SSID: " + ssid);
    SerialBT.println("Password: " + (password.length() > 0 ? "Set (" + String(password.length()) + " chars)" : "Not set"));
    SerialBT.println("Connection: " + String(wifiConnected ? "Connected" : "Disconnected"));
    if (wifiConnected) {
      SerialBT.println("IP Address: " + WiFi.localIP().toString());
      SerialBT.println("Signal Strength: " + String(WiFi.RSSI()) + " dBm");
    }
    SerialBT.println("-------------------");
  }
  else if (command == "CLEAR") {
    preferences.clear();
    ssid = "";
    password = "";
    WiFi.disconnect();
    wifiConnected = false;
    SerialBT.println("All WiFi credentials cleared!");
    Serial.println("Credentials cleared");
  }
  else {
    SerialBT.println("Unknown command: " + command);
    SerialBT.println("Available commands: SSID:, PASS:, CONNECT, STATUS, CLEAR");
  }
}

void connectToWiFi() {
  Serial.println("Connecting to: " + ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    SerialBT.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    wifiConnected = true;
    SerialBT.println("\nWiFi Connected!");
    SerialBT.println("IP Address: " + WiFi.localIP().toString());
    Serial.println("\nWiFi Connected!");
    Serial.println("IP: " + WiFi.localIP().toString());
  } else {
    SerialBT.println("\nFailed to connect to WiFi");
    Serial.println("\nConnection failed");
  }
}