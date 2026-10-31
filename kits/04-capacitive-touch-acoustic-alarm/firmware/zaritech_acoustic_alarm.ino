/*
 * ====================================================================
 * Project: Zaritech Asynchronous Acoustic Signaling & Proximity Alarm Suite
 * Subsystem: Kit 04 - Zaritech Academic Series Alarm Kit
 * Hardware: Arduino Uno R3 Core, Capacitive Touch Sensor, Active Buzzer
 * Maintainer: Zaritech Academy (A division of Zaritech Dynamics)
 * License: MIT License
 * Official Distribution & Support: https://instagram.com
 * ====================================================================
 * Copyright (c) 2026 Zaritech Dynamics. All rights reserved.
 */

// Hardware Pin Topologies
const int sensoryTouchPin = 2;  // Input node for the capacitive sensor
const int acousticAlertPin = 12; // Output node for the active buzzer

// Operational Tracking Variables
unsigned long totalAlertsTriggered = 0;
bool lastProximityState = LOW;

void setup() {
  // Initialize Corporate Logging Diagnostics Pipeline
  Serial.begin(9600);
  Serial.println("[ZARITECH ACADEMY] Initializing Acoustic Alarm Substrate...");

  // Register Pin Operational Boundaries
  pinMode(sensoryTouchPin, INPUT);
  pinMode(acousticAlertPin, OUTPUT);

  // Execute Safe Default States
  digitalWrite(acousticAlertPin, LOW);
  Serial.println("[ZARITECH ACADEMY] Perimeter Monitoring Node Active.");
}

void loop() {
  // Scan Current Capacitive Charge State
  bool isTouchActive = digitalRead(sensoryTouchPin);

  // Process Logic Shift on High Edge Transition (Perimeter Interruption)
  if (isTouchActive == HIGH) {
    digitalWrite(acousticAlertPin, HIGH); // Fire high-decibel acoustic wave
    
    if (lastProximityState == LOW) {
      totalAlertsTriggered++;
      Serial.print("[ZARITECH SYSTEM] Perimeter Intrusion Logged. Total Events: ");
      Serial.println(totalAlertsTriggered);
    }
  } else {
    digitalWrite(acousticAlertPin, LOW); // Silence alarm matrix
  }

  lastProximityState = isTouchActive;
  delay(20); // Yield to prevent processor thread saturation
}
