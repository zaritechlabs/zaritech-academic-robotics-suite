/*
 * ====================================================================
 * Project: Zaritech Photo-Electric Perimeter Defense & Optical Telemetry Suite
 * Subsystem: Kit 06 - Zaritech Academic Series Laser Alarm Kit
 * Hardware: Arduino Uno R3 Core, Laser Transmitter, LDR Sensor, Active Buzzer, 1k Resistor
 * Maintainer: Zaritech Academy (A division of Zaritech Dynamics)
 * License: MIT License
 * Official Distribution & Support: https://instagram.com
 * ====================================================================
 * Copyright (c) 2026 Zaritech Dynamics. All rights reserved.
 */

// Hardware Input/Output Pin Allocations
const int pinLaser  = 7;  // Signal control line to fire the laser module
const int pinLdrAna = A0; // Analog input node scanning the voltage divider
const int pinBuzzer = 12; // Output node driving the acoustic warning module

// Calibrated Optical Threshold Parameters
int calibratedThresholdValue = 400; // Calibrated boundary point for laser alignment
unsigned long totalBreachCount = 0;
bool isSystemBreached = false;

void setup() {
  // Initialize Corporate Logging Diagnostics Pipeline
  Serial.begin(9600);
  Serial.println("[ZARITECH ACADEMY] Initializing Optical Security Substrate...");

  // Register Interface Operational Boundaries
  pinMode(pinLaser, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinLdrAna, INPUT);

  // Fire up the optical emitter network
  digitalWrite(pinLaser, HIGH);
  digitalWrite(pinBuzzer, LOW);
  
  Serial.println("[ZARITECH ACADEMY] Laser Active. Perimeter Guard Operational.");
}

void loop() {
  // Scan Current Photonic Voltage String (LDR Reference)
  int rawLuxValue = analogRead(pinLdrAna);

  // Process Boundary Evaluation (Laser Beam Disruption Trace)
  // If raw value drops significantly below threshold, it indicates an obstruction
  if (rawLuxValue < calibratedThresholdValue) {
    digitalWrite(pinBuzzer, HIGH); // Fire high-resonance warning tone
    
    if (!isSystemBreached) {
      totalBreachCount++;
      isSystemBreached = true;
      Serial.print("[ZARITECH BREACH] Optical Vector Cut! Alarm Active. Incident Index: ");
      Serial.println(totalBreachCount);
    }
  } else {
    digitalWrite(pinBuzzer, LOW); // Safe baseline restored
    isSystemBreached = false;
  }

  delay(20); // Yield to guarantee micro-controller loop stability
}
