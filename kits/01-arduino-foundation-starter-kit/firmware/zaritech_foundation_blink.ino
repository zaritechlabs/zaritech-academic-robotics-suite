/*
 * ====================================================================
 * Project: Zaritech Arduino Foundation Starter Kit & GPIO Logic Array
 * Subsystem: Kit 01 - Zaritech Academic Series Starter Kit
 * Hardware: Arduino Uno R3 (ATmega328P DIP), 5x LEDs, 220R Resistors
 * Maintainer: Zaritech Academy (A division of Zaritech Dynamics)
 * License: MIT License
 * Official Distribution & Support: https://instagram.com
 * ====================================================================
 * Copyright (c) 2026 Zaritech Dynamics. All rights reserved.
 */

// Hardware Output Mapping Parameters
const int ledCount = 3;
const int ledPins[ledCount] = {8, 9, 10}; // Digital GPIO pins mapped to visual nodes

// Calibrated Timing Intervals
const int STEP_DELAY_MS = 200;

void setup() {
  // Initialize Corporate Logging Diagnostics Pipeline
  Serial.begin(9600);
  Serial.println("[ZARITECH ACADEMY] Initializing Foundation Starter Substrate...");

  // Register Digital GPIO Pins as Active Output Transistors
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // Ensure clean ground baseline on system boot
  }
  
  Serial.println("[ZARITECH ACADEMY] GPIO Output Matrix Operational. Commencing Loop...");
}

void loop() {
  // Execute Forward Sequential Shifting Pulse (Lojistik Takip Dizilimi)
  for (int i = 0; i < ledCount; i++) {
    Serial.print("[ZARITECH GPIO] Firing Node Pin: ");
    Serial.println(ledPins[i]);
    
    digitalWrite(ledPins[i], HIGH); // Engage Current Path
    delay(STEP_DELAY_MS);
    digitalWrite(ledPins[i], LOW);  // Disengage Current Path
  }

  // Execute Reverse Sequential Shifting Pulse for Balanced Visual Loop
  for (int i = ledCount - 2; i > 0; i--) {
    Serial.print("[ZARITECH GPIO] Firing Node Pin: ");
    Serial.println(ledPins[i]);
    
    digitalWrite(ledPins[i], HIGH);
    delay(STEP_DELAY_MS);
    digitalWrite(ledPins[i], LOW);
  }
}
