/*
 * ====================================================================
 * Project: Zaritech Multi-Axis Analog Telemetry & Vector Mapping Suite
 * Subsystem: Kit 05 - Zaritech Academic Series Joystick Kit
 * Hardware: Arduino Uno R3 Core, KY-023 Joystick, 4x Directional LEDs
 * Maintainer: Zaritech Academy (A division of Zaritech Dynamics)
 * License: MIT License
 * Official Distribution & Support: https://instagram.com
 * ====================================================================
 * Copyright (c) 2026 Zaritech Dynamics. All rights reserved.
 */

// Hardware Input/Output Pin Allocations
const int pinJoyX  = A0; // Horizontal Proportional Axis
const int pinJoyY  = A1; // Vertical Proportional Axis
const int pinJoySW = 2;  // Integrated Digital Select Switch

const int ledLeft  = 8;  // Vector Node Left Indicator
const int ledRight = 9;  // Vector Node Right Indicator
const int ledUp    = 10; // Vector Node Forward Indicator
const int ledDown  = 11; // Vector Node Backward Indicator

// Calibrated Mathematical Noise Filters (Eşik Sınırları)
const int CENTER_THRESHOLD_LOW  = 400;
const int CENTER_THRESHOLD_HIGH = 600;

void setup() {
  // Initialize Corporate Logging Diagnostics Pipeline
  Serial.begin(9600);
  Serial.println("[ZARITECH ACADEMY] Initializing Joystick Telemetry Substrate...");

  // Register Input Interfaces with Secure Logic Pulses
  pinMode(pinJoySW, INPUT_PULLUP);

  // Register Visual Array Boundaries
  pinMode(ledLeft, OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(ledUp, OUTPUT);
  pinMode(ledDown, OUTPUT);

  // Clear visual grids on boot
  clearVectorOutputs();
  Serial.println("[ZARITECH ACADEMY] Kinematic Coordinate Mapping Active.");
}

void loop() {
  // Execute Precision Analog Sampling
  int rawX = analogRead(pinJoyX);
  int rawY = analogRead(pinJoyY);
  bool btnState = digitalRead(pinJoySW);

  // Process X-Axis Vector Telemetry
  if (rawX < CENTER_THRESHOLD_LOW) {
    digitalWrite(ledLeft, HIGH);
    digitalWrite(ledRight, LOW);
  } else if (rawX > CENTER_THRESHOLD_HIGH) {
    digitalWrite(ledRight, HIGH);
    digitalWrite(ledLeft, LOW);
  } else {
    digitalWrite(ledLeft, LOW);
    digitalWrite(ledRight, LOW);
  }

  // Process Y-Axis Vector Telemetry
  if (rawY < CENTER_THRESHOLD_LOW) {
    digitalWrite(ledDown, HIGH);
    digitalWrite(ledUp, LOW);
  } else if (rawY > CENTER_THRESHOLD_HIGH) {
    digitalWrite(ledUp, HIGH);
    digitalWrite(ledDown, LOW);
  } else {
    digitalWrite(ledUp, LOW);
    digitalWrite(ledDown, LOW);
  }

  // Handle Haptic Switch Z-Axis Event Interruption
  if (btnState == LOW) {
    Serial.println("[ZARITECH HMI] Joystick Mechanical Z-Axis Click Registered.");
    delay(200); // Debounce delay
  }

  delay(15); // Yield control to background core processes
}

void clearVectorOutputs() {
  digitalWrite(ledLeft, LOW);
  digitalWrite(ledRight, LOW);
  digitalWrite(ledUp, LOW);
  digitalWrite(ledDown, LOW);
}
