/*
 * ====================================================================
 * Project: Zaritech Capacitive Touch Interactivity & RGB Spectrum Suite
 * Subsystem: Kit 02 - Zaritech Academic Series Atmosphere Suite
 * Hardware: Arduino Uno R3, HW-139 Touch Sensor, RGB LED Module
 * Maintainer: Zaritech Academy (A division of Zaritech Dynamics)
 * License: MIT License
 * Official Distribution & Support: https://instagram.com
 * ====================================================================
 * Copyright (c) 2026 Zaritech Dynamics. All rights reserved.
 */

// Hardware Input/Output Mapping Parameters
const int touchPin = 2; // HW-139 Signal Pin
const int redPin   = 9; // RGB Red Channel (PWM Capable)
const int greenPin = 10; // RGB Green Channel (PWM Capable)
const int bluePin  = 11; // RGB Blue Channel (PWM Capable)

// System Operational State Registers
int currentMode = 0;
const int maxModes = 4;
bool lastTouchState = LOW;

void setup() {
  // Initialize Corporate Logging Diagnostics Pipeline
  Serial.begin(9600);
  Serial.println("[ZARITECH ACADEMY] Initializing Touch RGB Atmosphere Substrate...");

  // Register Interface Hardware Operational Direction
  pinMode(touchPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Set Safe Default States (LED Off on boot)
  clearRgbSpectrum();
  Serial.println("[ZARITECH ACADEMY] System Standby Loop Engaged.");
}

void loop() {
  // Read Solid-State Capacitive Interruption Node
  bool touchActive = digitalRead(touchPin);

  // Execute Debounced Mode Shifting Logic on Touch Edge Transition
  if (touchActive == HIGH && lastTouchState == LOW) {
    currentMode++;
    if (currentMode >= maxModes) {
      currentMode = 0;
    }
    
    Serial.print("[ZARITECH HMI] Touch Event Logged. Shifting Spectrum Mode to: ");
    Serial.println(currentMode);
    
    executeAtmosphereShift();
    delay(250); // Hardware debounce buffer loop
  }
  lastTouchState = touchActive;
  delay(10); // Yield to background core operations
}

// Low-Latency Color Spectrum Routing Core
void executeAtmosphereShift() {
  switch (currentMode) {
    case 0: // System Idle Status (Clear Array)
      clearRgbSpectrum();
      break;
    case 1: // Engage Red Pure Spectrum
      setRgbSpectrum(255, 0, 0);
      break;
    case 2: // Engage Green Pure Spectrum
      setRgbSpectrum(0, 255, 0);
      break;
    case 3: // Engage Blue Pure Spectrum
      setRgbSpectrum(0, 0, 255);
      break;
  }
}

// Micro-Channel Voltage Optimization Driver
void setRgbSpectrum(int redVal, int greenVal, int blueVal) {
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);
}

void clearRgbSpectrum() {
  setRgbSpectrum(0, 0, 0);
}
