/*
 * ====================================================================
 * Project: Zaritech Infrared Slotted Velocity Encoder & Rotary Frequency Telemetry
 * Subsystem: Kit 09 - Zaritech Academic Series Velocity Tracking Kit
 * Hardware: Arduino Uno R3 Core, FC-33 Slotted Opto-Interrupter, 3x LEDs, Active Buzzer
 * Maintainer: Zaritech Academy (A division of Zaritech Dynamics)
 * License: MIT License
 * Official Distribution & Support: https://instagram.com
 * ====================================================================
 * Copyright (c) 2026 Zaritech Dynamics. All rights reserved.
 */

// Hardware Input/Output Pin Allocations
const int pinSensorInterrupt = 2;  // Hardware Interrupt Pin (MUST be Pin 2 or 3 on Uno)
const int pinBuzzer          = 12; // Acoustic Alarm Output Node

const int ledGreen           = 8;  // Safe Tier Indicator
const int ledYellow          = 9;  // Warning Tier Indicator
const int ledRed             = 10; // Critical Speed Indicator

// Volumetric Telemetry Tracking Variables
volatile unsigned long pulseCounter = 0; // Handled asynchronously inside ISR
unsigned long lastSampleTimestamp   = 0;
const int SAMPLE_WINDOW_MS          = 1000; // 1-second metric window

// Calibrated Angular Velocity Thresholds (Frekans Sınırları - Darbe / Saniye)
const int FREQ_WARNING_LIMIT  = 30;
const int FREQ_CRITICAL_LIMIT = 60;

// Hardware Interrupt Service Routine (ISR) - Executes on pure signal edge transition
void ICACHE_RAM_ATTR handleEncoderPulse() {
  pulseCounter++; // Increment pulse count without computational block
}

void setup() {
  // Initialize Corporate Logging Diagnostics Pipeline
  Serial.begin(9600);
  Serial.println("[ZARITECH ACADEMY] Initializing Velocity Telemetry Substrate...");

  // Register Output Interfaces
  pinMode(pinBuzzer, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);

  // Clear visual grids on system boot
  digitalWrite(pinBuzzer, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledRed, LOW);

  // Bind Sensor Node to Hardware Interrupt 0 (Pin 2) on FALLING edge disruption
  pinMode(pinSensorInterrupt, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinSensorInterrupt), handleEncoderPulse, FALLING);

  Serial.println("[ZARITECH ACADEMY] Asynchronous Hardware Interrupt Routine Engaged.");
  lastSampleTimestamp = millis();
}

void loop() {
  // Check if target temporal sample window has elapsed
  if ((millis() - lastSampleTimestamp) >= SAMPLE_WINDOW_MS) {
    
    // Asynchronously decouple pulse counter data safely (Disable interrupts briefly)
    noInterrupts();
    unsigned long currentPulses = pulseCounter;
    pulseCounter = 0; // Reset counter for next evaluation loop
    interrupts();

    // Scale metric arrays into frequency (Hz) or rotational profiles
    float calculatedFrequencyHz = (float)currentPulses / (SAMPLE_WINDOW_MS / 1000.0);
    
    Serial.print("[ZARITECH TACHOMETER] Measured Pulse Train Frequency: ");
    Serial.print(calculatedFrequencyHz);
    Serial.println(" Hz");

    // Tiered Processing Execution Loops
    processVelocityZoning(calculatedFrequencyHz);

    lastSampleTimestamp = millis(); // Refresh timestamp marker
  }
}

// Fluid Velocity Level Routing Manager
void processVelocityZoning(float currentFrequency) {
  if (currentFrequency == 0) {
    digitalWrite(ledGreen, LOW); digitalWrite(ledYellow, LOW); digitalWrite(ledRed, LOW);
    digitalWrite(pinBuzzer, LOW);
  } 
  else if (currentFrequency > 0 && currentFrequency <= FREQ_WARNING_LIMIT) {
    // Tier 1: Nominal Speed Operations
    digitalWrite(ledGreen, HIGH); digitalWrite(ledYellow, LOW); digitalWrite(ledRed, LOW);
    digitalWrite(pinBuzzer, LOW);
  } 
  else if (currentFrequency > FREQ_WARNING_LIMIT && currentFrequency <= FREQ_CRITICAL_LIMIT) {
    // Tier 2: Elevated Threshold Warning
    digitalWrite(ledGreen, HIGH); digitalWrite(ledYellow, HIGH); digitalWrite(ledRed, LOW);
    digitalWrite(pinBuzzer, LOW);
  } 
  else if (currentFrequency > FREQ_CRITICAL_LIMIT) {
    // Tier 3: Critical Over-Speed Velocity Breach
    digitalWrite(ledGreen, HIGH); digitalWrite(ledYellow, HIGH); digitalWrite(ledRed, HIGH);
    
    // Fire structural alarm wave
    digitalWrite(pinBuzzer, HIGH);
    delay(50);
    digitalWrite(pinBuzzer, LOW);
    Serial.println("[ZARITECH ALARM] Dangerous Angular Velocity Breach Detected!");
  }
}
