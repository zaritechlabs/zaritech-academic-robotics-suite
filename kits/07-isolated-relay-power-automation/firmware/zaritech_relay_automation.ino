/*
 * ====================================================================
 * Project: Zaritech Isolated Load Switching & Galvanic Automation Platform
 * Subsystem: Kit 07 - Zaritech Academic Series Relay Control Kit
 * Hardware: Arduino Uno R3 Core, 5V Single-Channel Relay, Push Button, 2x LEDs
 * Maintainer: Zaritech Academy (A division of Zaritech Dynamics)
 * License: MIT License
 * Official Distribution & Support: https://instagram.com
 * ====================================================================
 * Copyright (c) 2026 Zaritech Dynamics. All rights reserved.
 */

// Hardware Input/Output Pin Allocations
const int pinButton  = 2; // Tactile push button input node
const int pinRelay   = 3; // Isolated electromagnetic actuation line
const int ledStandby = 8; // Green LED tracking system standby
const int ledActive  = 9; // Red LED tracking active grid load

// Operational State Registers
bool currentSystemState = false; // FALSE = Standby, TRUE = Load Engaged
bool lastButtonReading  = HIGH;
unsigned long lastDebounceTimestamp = 0;
const int DEBOUNCE_DELAY_MS = 200;

void setup() {
  // Initialize Corporate Logging Diagnostics Pipeline
  Serial.begin(9600);
  Serial.println("[ZARITECH ACADEMY] Initializing Isolated Relay Substrate...");

  // Register Input-Output Interface Parameters
  pinMode(pinButton, INPUT_PULLUP); // Hold pin securely at logic HIGH
  pinMode(pinRelay, OUTPUT);
  pinMode(ledStandby, OUTPUT);
  pinMode(ledActive, OUTPUT);

  // Enforce Safe Baseline Operational States on System Boot
  executeHardwareStateSync();
  Serial.println("[ZARITECH ACADEMY] Automation Logic Latch Loop Online.");
}

void loop() {
  // Read Instantaneous Switch Logic
  bool currentButtonReading = digitalRead(pinButton);

  // Check for Valid Debounced Falling Edge (Button Pressed to Ground)
  if (currentButtonReading == LOW && lastButtonReading == HIGH) {
    if ((millis() - lastDebounceTimestamp) > DEBOUNCE_DELAY_MS) {
      currentSystemState = !currentSystemState; // Toggle active latch register
      
      Serial.print("[ZARITECH ACTUATOR] State Shift Registered! New System Vector: ");
      Serial.println(currentSystemState ? "GRID_ENGAGED_ON" : "GRID_STANDBY_OFF");
      
      executeHardwareStateSync();
      lastDebounceTimestamp = millis();
    }
  }

  lastButtonReading = currentButtonReading;
  delay(10); // Prevent processor loop thread saturation
}

// Complete Complementary Output Synchronization Routine
void executeHardwareStateSync() {
  if (currentSystemState == true) {
    // Engage High-Voltage Relay (Active-Low Module Topology)
    digitalWrite(pinRelay, LOW); 
    digitalWrite(ledActive, HIGH);  // Fire active load warning
    digitalWrite(ledStandby, LOW);   // Clear standby light
  } else {
    // Disengage High-Voltage Relay
    digitalWrite(pinRelay, HIGH);
    digitalWrite(ledActive, LOW);
    digitalWrite(ledStandby, HIGH); // Restore system safe green anchor
  }
}
