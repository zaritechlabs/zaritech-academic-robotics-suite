/*
 * ====================================================================
 * Project: Zaritech Kinematic Steering Array & Dual-Axis Proportional Control Platform
 * Subsystem: Kit 08 - Zaritech Academic Series Kinematic Joystick Suite
 * Hardware: Arduino Uno R3 Core, Analog Joystick Module, Push Button, 2x Status LEDs
 * Maintainer: Zaritech Academy (A division of Zaritech Dynamics)
 * License: MIT License
 * Official Distribution & Support: https://instagram.com
 * ====================================================================
 * Copyright (c) 2026 Zaritech Dynamics. All rights reserved.
 */

// Hardware Input/Output Pin Allocations
const int pinAnalogX = A0;   // Horizontal proportional coordinate axis
const int pinAnalogY = A1;   // Vertical proportional coordinate axis
const int pinButton  = 2;    // External manual override tact button
const int ledGreen   = 8;    // Target visual status indicator 1
const int ledRed     = 9;    // Target visual status indicator 2

// Calibrated Mathematical Deadzone Filters (Ölü Bölge Eşikleri)
const int AXIS_DEADZONE_LOW  = 350;
const int AXIS_DEADZONE_HIGH = 670;

void setup() {
  // Initialize Corporate Logging Diagnostics Pipeline
  Serial.begin(9600);
  Serial.println("[ZARITECH ACADEMY] Initializing Kinematic Joystick Substrate...");

  // Register Operational Logic Directions
  pinMode(pinButton, INPUT_PULLUP); // Safe internal pull-up lock
  pinMode(pinGreen, OUTPUT);
  pinMode(pinRed, OUTPUT);

  // Clear logic signals on boot
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, LOW);
  
  Serial.println("[ZARITECH ACADEMY] Kinematic Steering Loop Online.");
}

void loop() {
  // Sample Proportional Voltage Tracks
  int xReading = analogRead(pinAnalogX);
  int yReading = analogRead(pinAnalogY);
  bool overrideTriggered = !digitalRead(pinButton); // Active-LOW mapping inversion

  // Process Kinematic Coordinate Vector Bounds
  // Check if either axis exceeds predefined mechanical deadzones
  if (xReading > AXIS_DEADZONE_HIGH || yReading > AXIS_DEADZONE_HIGH) {
    digitalWrite(ledGreen, HIGH); // Firing forward alignment indicators
    digitalWrite(ledRed, LOW);
  } else if (xReading < AXIS_DEADZONE_LOW || yReading < AXIS_DEADZONE_LOW) {
    digitalWrite(ledRed, HIGH);   // Firing backward alignment indicators
    digitalWrite(ledGreen, LOW);
  } else {
    // Kinematic controller is at relaxed center baseline
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, LOW);
  }

  // Handle Manual Override Interrupt Event
  if (overrideTriggered == true) {
    Serial.println("[ZARITECH HMI] Manual Override System Interruption Acknowledged!");
    
    // Physical state confirmation blink routine
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledGreen, HIGH); digitalWrite(ledRed, HIGH);
      delay(80);
      digitalWrite(ledGreen, LOW);  digitalWrite(ledRed, LOW);
      delay(80);
    }
  }

  delay(15); // Yield control to prevent system thread starvation
}
