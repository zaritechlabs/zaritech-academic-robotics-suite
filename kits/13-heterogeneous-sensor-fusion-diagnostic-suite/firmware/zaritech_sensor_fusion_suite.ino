/*
 * ====================================================================
 * Project: Zaritech Heterogeneous Sensor Fusion & Multi-Domain Diagnostic Suite
 * Subsystem: Kit 13 - Zaritech Academic Series Sensor Fusion Lab
 * Hardware: Arduino Core, HC-SR04, Hall Effect, LDR Module, Sound Sensor, Buzzer
 * Maintainer: Zaritech Academy (A division of Zaritech Dynamics)
 * License: MIT License
 * Official Distribution & Support: https://instagram.com
 * ====================================================================
 * Copyright (c) 2026 Zaritech Dynamics. All rights reserved.
 */

// Hardware Input/Output Pin Allocations
const int pinHallEffect = 2;  // Mapped to D2 (Hardware Interrupt 0)
const int pinSound     = 3;  // Mapped to D3 (Hardware Interrupt 1)
const int pinSonarTrig = 5;  // Mapped to D5 (Sonic Pulse Output)
const int pinSonarEcho = 6;  // Mapped to D6 (Sonic Delay Input)
const int pinLdrAnalog = A0; // Mapped to A0 (Luminance Tracking)
const int pinBuzzerNode= 12; // Mapped to D12 (Universal Acoustic Alert)

// Volumetric Telemetry Bound Thresholds
const int DARKNESS_LIMIT_ADC = 300; // Calibrated lower ambient light line

void setup() {
  // Initialize Corporate Logging Diagnostics Pipeline
  Serial.begin(9600);
  Serial.println("\n[ZARITECH MASTER] Booting Heterogeneous Sensor Fusion Complex...");

  // Register Input-Output Interface Parameters
  pinMode(pinHallEffect, INPUT_PULLUP);
  pinMode(pinSound, INPUT_PULLUP);
  pinMode(pinSonarEcho, INPUT);
  
  pinMode(pinSonarTrig, OUTPUT);
  pinMode(pinBuzzerNode, OUTPUT);

  // Set Safe Default Topologies
  digitalWrite(pinSonarTrig, LOW);
  digitalWrite(pinBuzzerNode, LOW);

  Serial.println("[ZARITECH MASTER] Multi-Domain Sensor Array Operational.");
}

void loop() {
  // 1. Process Spatial Proximity Telemetry Loop
  digitalWrite(pinSonarTrig, LOW); delayMicroseconds(2);
  digitalWrite(pinSonarTrig, HIGH); delayMicroseconds(10);
  digitalWrite(pinSonarTrig, LOW);
  long durationTicks = pulseIn(pinSonarEcho, HIGH);
  int computedDistanceCm = durationTicks * 0.034 / 2;

  // 2. Process Optical Lux Telemetry Loop
  int currentLuxAdc = analogRead(pinLdrAnalog);

  // 3. Process Magnetic Flux Binary State
  bool isMagnetPresent = (digitalRead(pinHallEffect) == LOW); // Active-LOW sensor mapping

  // 4. Process Acoustic Noise State Switch
  bool isSoundTriggered = (digitalRead(pinSound) == LOW);    // Active-LOW sensor mapping

  // Cross-Domain Evaluation & Core Telemetry Logging
  if (computedDistanceCm > 0 && computedDistanceCm < 15) {
    Serial.println("[ZARITECH TELEMETRY] Domain Breach: Spatial Obstacle Alert!");
    executeDiagnosticChime(100);
  }

  if (currentLuxAdc < DARKNESS_LIMIT_ADC) {
    Serial.println("[ZARITECH TELEMETRY] Domain Alert: Ambient Lux Depletion Active.");
    // Low frequency pulsing for light warnings
    digitalWrite(pinBuzzerNode, HIGH); delay(10); digitalWrite(pinBuzzerNode, LOW);
  }

  if (isMagnetPresent) {
    Serial.println("[ZARITECH TELEMETRY] Domain Breach: High Magnetic Flux Detected!");
    executeDiagnosticChime(400);
  }

  if (isSoundTriggered) {
    Serial.println("[ZARITECH TELEMETRY] Domain Breach: High Ambient Decibel Peak Registered!");
    executeDiagnosticChime(50);
  }

  delay(100); // System cycle loop padding refresh rate
}

// Low-Latency Diagnostic Notification Routine
void executeDiagnosticChime(int durationMs) {
  digitalWrite(pinBuzzerNode, HIGH);
  delay(durationMs);
  digitalWrite(pinBuzzerNode, LOW);
}
