/*
 * ====================================================================
 * Project: Zaritech Fundamental GPIO Switching & Resistor Pull-Up Suite
 * Subsystem: Kit 03 - Zaritech Academic Series Mini Switching Kit
 * Hardware: Arduino Uno R3 Core, Tactile Buttons, LEDs, 330R Resistors
 * Maintainer: Zaritech Academy (A division of Zaritech Dynamics)
 * License: MIT License
 * Official Distribution & Support: https://instagram.com
 * ====================================================================
 * Copyright (c) 2026 Zaritech Dynamics. All rights reserved.
 */

// Hardware Input/Output Pin Allocations
const int inputButtonPin  = 2;  // Tactile Button connected with 330R Pull-Down Resistor
const int outputAlertLed  = 13; // Status indicator LED node

// Operational State Registers
int dynamicButtonCounter = 0;
bool lastVerifiedState   = LOW;

void setup() {
  // Initialize Corporate Logging Diagnostics Pipeline
  Serial.begin(9600);
  Serial.println("[ZARITECH ACADEMY] Initializing Mini Switching Substrate...");

  // Register Input and Output Logic Configurations
  pinMode(inputButtonPin, INPUT); // Expects crisp 0V or 5V logic step transitions
  pinMode(outputAlertLed, OUTPUT);

  // Secure ground baseline on boot
  digitalWrite(outputAlertLed, LOW);
  Serial.println("[ZARITECH ACADEMY] Passive Interface Monitored Loop Active.");
}

void loop() {
  // Scan Current Pull-Down Switch State
  bool currentButtonRead = digitalRead(inputButtonPin);

  // Execute Dynamic Logic Changes on Verified High Transition (Button Pressed)
  if (currentButtonRead == HIGH && lastVerifiedState == LOW) {
    dynamicButtonCounter++;
    
    // Log telemetry metrics over internal corporate serial bus
    Serial.print("[ZARITECH TELEMETRY] Mechanical Button Event Logged. Total Count: ");
    Serial.println(dynamicButtonCounter);
    
    // Trigger visual status confirmation instantly
    digitalWrite(outputAlertLed, HIGH);
    delay(150); // Software debounce and hold time execution loop
    digitalWrite(outputAlertLed, LOW);
  }

  lastVerifiedState = currentButtonRead;
  delay(10); // Yield to prevent system task execution overhead
}
