/*
 * ====================================================================
 * Project: Zaritech Dual-MCU Prototyping & Sensor Shield Infrastructure
 * Subsystem: Kit 10 - Zaritech Advanced Series Backplane Shield Platform
 * Hardware: Arduino Uno R3 / Nano V3, Sensor Shield V5.0, 5V Relay, Active Buzzer, LEDs
 * Maintainer: Zaritech Academy (A division of Zaritech Dynamics)
 * License: MIT License
 * Official Distribution & Support: https://instagram.com
 * ====================================================================
 * Copyright (c) 2026 Zaritech Dynamics. All rights reserved.
 */

// Hardware Input/Output Pin Allocations (Sensor Shield Mapped)
const int pinInputTrigger   = 2;  // Mapped to Digital SVG Port D2 (Hardware Interrupt)
const int pinRelayActuator  = 3;  // Mapped to Digital SVG Port D3 (Isolated Actuation)
const int pinBuzzerNode     = 12; // Mapped to Digital SVG Port D12 (Acoustic Indicator)
const int pinStatusLed      = 8;  // Mapped to Digital SVG Port D8 (Visual Feedback)

// Operational Volumetric Registers
volatile bool isActuatorTriggered = false;
unsigned long lastDebounceTime     = 0;
const int HARDWARE_DEBOUNCE_MS     = 250;

// Hardware Interrupt Service Routine (ISR)
void ICACHE_RAM_ATTR handleShieldInterruption() {
  if ((millis() - lastDebounceTime) > HARDWARE_DEBOUNCE_MS) {
    isActuatorTriggered = !isActuatorTriggered; // Toggle the active latch state asynchronously
    lastDebounceTime = millis();
  }
}

void setup() {
  // Initialize Corporate Logging Diagnostics Pipeline
  Serial.begin(9600);
  Serial.println("[ZARITECH ACADEMY] Initializing Backplane Sensor Shield Substrate...");

  // Register Interface Pins for Output States
  pinMode(pinRelayActuator, OUTPUT);
  pinMode(pinBuzzerNode, OUTPUT);
  pinMode(pinStatusLed, OUTPUT);

  // Enforce Safe Baseline Operational States on Boot
  digitalWrite(pinRelayActuator, HIGH); // Disengage active-low relay array loop
  digitalWrite(pinBuzzerNode, LOW);
  digitalWrite(pinStatusLed, LOW);

  // Bind Input Pin with Secure Pull-Up Lock to Hardware Interrupt 0 (Pin 2)
  pinMode(pinInputTrigger, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinInputTrigger), handleShieldInterruption, FALLING);

  Serial.println("[ZARITECH ACADEMY] Dedicated Sensor Shield Interrupt Vector Active.");
}

void loop() {
  // Static state caching container
  static bool lastProcessedState = false;

  // Track if an asynchronous state toggle event has been verified
  if (isActuatorTriggered != lastProcessedState) {
    lastProcessedState = isActuatorTriggered;
    
    Serial.print("[ZARITECH BACKPLANE] Input State Change Sync. New System Matrix: ");
    Serial.println(isActuatorTriggered ? "ACTUATOR_ENGAGED_ON" : "STANDBY_OFF");
    
    executeHardwareSystemSync(isActuatorTriggered);
  }
  
  delay(10); // Prevent process execution starvation loop
}

// Complete System Backplane Sync Driver
void executeHardwareSystemSync(bool engageState) {
  if (engageState == true) {
    digitalWrite(pinRelayActuator, LOW);   // Engage High-Voltage Load Link (Active-Low)
    digitalWrite(pinStatusLed, HIGH);      // Light up tracking diagnostic led
    
    // Fire localized sharp haptic tone
    digitalWrite(pinBuzzerNode, HIGH);
    delay(80);
    digitalWrite(pinBuzzerNode, LOW);
  } else {
    digitalWrite(pinRelayActuator, HIGH);  // Disengage High-Voltage Load Link
    digitalWrite(pinStatusLed, LOW);       // Clear diagnostic indicator
    
    // Fire brief double click buzzer tone
    digitalWrite(pinBuzzerNode, HIGH); delay(40); digitalWrite(pinBuzzerNode, LOW); delay(40);
    digitalWrite(pinBuzzerNode, HIGH); delay(40); digitalWrite(pinBuzzerNode, LOW);
  }
}
