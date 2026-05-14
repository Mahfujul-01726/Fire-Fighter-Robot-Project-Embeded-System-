// Code For ESP(Gas Sensor + Flame Sensor)
#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "wifi name";
const char* password = "wifi pass";
unsigned long channelNumber = 3357174;
const char* writeAPIKey = "4PP0T6L2GXGXAR4M";
WiFiClient client;

// Pins
#define MQ_PIN 34
#define FLAME_PIN 35
#define GAS_THRESHOLD 600
#define FLAME_THRESHOLD 300

// Added based on SYSTEM_ARCHITECTURE.md for active fire suppression:
#define RELAY_PIN 26

unsigned long lastThingSpeakUpdate = 0;
const unsigned long updateInterval = 15000; // 15 seconds interval for ThingSpeak

void setup() {
  Serial.begin(115200);
  
  // Initialize Relay for Water Pump
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Ensure pump is OFF initially

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n WiFi Connected");
  ThingSpeak.begin(client);
}

void loop() {
  int gasValue = analogRead(MQ_PIN);
  int flameValue = analogRead(FLAME_PIN);
  
  bool hazardDetected = false;

  // Real-time Hazard Evaluation
  if (gasValue > GAS_THRESHOLD) {
    hazardDetected = true;
  }
  if (flameValue < FLAME_THRESHOLD) {
    hazardDetected = true;
  }

  // Instant Actuation: Turn ON Water Pump Relay if Fire or Gas detected
  if (hazardDetected) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }

  // Non-blocking ThingSpeak update every 15 seconds
  if (millis() - lastThingSpeakUpdate >= updateInterval || lastThingSpeakUpdate == 0) {
    Serial.print("Gas: ");
    Serial.print(gasValue);
    Serial.print(" | Flame: ");
    Serial.println(flameValue);
    
    if (gasValue > GAS_THRESHOLD) {
      Serial.println(" Gas Detected!");
    }
    if (flameValue < FLAME_THRESHOLD) {
      Serial.println(" Flame Detected!");
    } else {
      Serial.println(" No Flame");
    }

    ThingSpeak.setField(1, gasValue);
    ThingSpeak.setField(2, flameValue);
    int status = ThingSpeak.writeFields(channelNumber, writeAPIKey);
    if (status == 200) {
      Serial.println("Data sent to ThingSpeak");
    } else {
      Serial.print(" Error sending data. Code: ");
      Serial.println(status);
    }
    Serial.println("----------------------");
    
    lastThingSpeakUpdate = millis();
  }
  
  delay(100); // Short delay for loop stability while maintaining real-time relay response
}
