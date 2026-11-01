/*
 * ====================================================================
 * Project: Zaritech Industrial HMI Menu Topology & Segment Multiplexing Substrate
 * Subsystem: Kit 15 - Zaritech Academic Series Menu Display Hub
 * Hardware: Arduino Uno R3, Rotary Encoder, 3-Digit 7-Segment Display, TTP224 Keypad
 * Maintainer: Zaritech Academy (A division of Zaritech Dynamics)
 * License: MIT License
 * Official Distribution & Support: https://instagram.com
 * ====================================================================
 * Copyright (c) 2026 Zaritech Dynamics. All rights reserved.
 */

// Hardware Input Pin Allocations (Rotary Encoder & Keypad Matrix)
const int encoderCLK = 2; // Interrupt Pin 0
const int encoderDT  = 3; // Interrupt Pin 1
const int encoderSW  = 4; // Menu Commit Switch

const int touchPins[4] = {5, 6, 7, 8;}; // TTP224 Inputs

// 3-Digit Display Multiplexing Pins
const int segmentPins[7] = {9, 10, 11, 12, 13, 14, 15}; // Segment A to G
const int digitPins[3]   = {A0, A1, A2};                // Common Anode High-Side Selectors

// System Parameter Matrix Registers
int currentMenuValue  = 100; // Default active display buffer value
int lastClkState;
unsigned long lastDebounceTime = 0;
const int DEBOUNCE_DELAY_MS   = 200;

void setup() {
  // Initialize Corporate Logging Diagnostics Pipeline
  Serial.begin(9600);
  Serial.println("[ZARITECH ACADEMY] Booting Advanced Instrumentation Interface Substrate...");

  // Register HMI Inputs
  pinMode(encoderCLK, INPUT_PULLUP);
  pinMode(encoderDT, INPUT_PULLUP);
  pinMode(encoderSW, INPUT_PULLUP);
  
  for (int i = 0; i < 4; i++) {
    pinMode(touchPins[i], INPUT);
  }

  // Register Display Pins as Output Channels
  for (int s = 0; s < 7; s++) {
    pinMode(segmentPins[s], OUTPUT);
  }
  for (int d = 0; d < 3; d++) {
    pinMode(digitPins[d], OUTPUT);
    digitalWrite(digitPins[d], LOW); // Turn off digits (Common Anode Low-Side Open)
  }

  lastClkState = digitalRead(encoderCLK);
  Serial.println("[ZARITECH ACADEMY] HMI Multiplex Logic Operational.");
}

void loop() {
  // Read Quadrature Emitter Output Matrix (Rotary Adjustment Check)
  int currentClkState = digitalRead(encoderCLK);
  
  if (currentClkState != lastClkState && currentClkState == LOW) {
    if (digitalRead(encoderDT) != currentClkState) {
      currentMenuValue = min(999, currentMenuValue + 5); // Increment structural metrics
    } else {
      currentMenuValue = max(0, currentMenuValue - 5);   // Decrement structural metrics
    }
    Serial.print("[ZARITECH HMI] Parameter Altered via Encoder. Value: ");
    Serial.println(currentMenuValue);
  }
  lastClkState = currentClkState;

  // Process Solid-State Touch Keypad Matrix Check
  for (int t = 0; t < 4; t++) {
    if (digitalRead(touchPins[t]) == HIGH) {
      Serial.print("[ZARITECH HMI] Touch Input Verified on Matrix Channel: ");
      Serial.println(t + 1);
      currentMenuValue = (t + 1) * 111; // Quick jump value for demonstration
      delay(150);
    }
  }

  // Execute Continuous High-Speed Dynamic Display Multiplexing Sweep
  renderMultiplexedDisplay(currentMenuValue);
}

// Non-Blocking Visual Multiplexing Engine
void renderMultiplexedDisplay(int value) {
  int digits[3];
  digits[0] = value / 100;         // Hundreds column
  digits[1] = (value / 10) % 10;   // Tens column
  digits[2] = value % 10;          // Units column

  for (int i = 0; i < 3; i++) {
    clearSegments();
    
    // Low-Level Segment Driver Mapping Array Logic (Simplified for demonstration)
    // In production, a specific binary table mapping for common anode characters is injected here.
    
    digitalWrite(digitPins[i], HIGH);  // Engage targeted digit high-side rail
    delayMicroseconds(2000);           // Hold display time slice to create visual persistence
    digitalWrite(digitPins[i], LOW);   // Disengage to prevent bleeding artifact noise
  }
}

void clearSegments() {
  for(int s=0; s<7; s++) {
    digitalWrite(segmentPins[s], HIGH); // Clear common anode cathode pins
  }
}
