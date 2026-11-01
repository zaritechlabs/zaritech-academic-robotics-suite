/*
 * ====================================================================
 * Project: Zaritech Spatial Proximity Mapping & Interactive OLED UI Substrate
 * Subsystem: Kit 11 - Zaritech Academic Series Spatial UI Hub
 * Hardware: Arduino Uno R3, I2C OLED (SSD1306), HC-SR04, Joystick, Active Buzzer, LEDs
 * Maintainer: Zaritech Academy (A division of Zaritech Dynamics)
 * License: MIT License
 * Official Distribution & Support: https://instagram.com
 * ====================================================================
 * Copyright (c) 2026 Zaritech Dynamics. All rights reserved.
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Graphical Environment Geometry Definitions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Hardware Pin Topology Mapping
const int trigPin   = 5;  // Ultrasonic Pulse Trigger
const int echoPin   = 6;  // Ultrasonic Logic Return Echo
const int buzzerPin = 12; // Acoustic Alert Control Node

const int ledGreen  = 8;  // Distance Zone Safe Light
const int ledYellow = 9;  // Distance Zone Warning Light
const int ledRed    = 10; // Distance Zone Critical Light

void setup() {
  // Initialize Corporate Logging Diagnostics Pipeline
  Serial.begin(9600);
  Serial.println("[ZARITECH ACADEMY] Initializing Spatial Telemetry Substrate...");

  // Register Pin Operational Environments
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);

  // Clear hardware signals on initialization
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledRed, LOW);

  // Initialize Local I2C Display System
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("[ZARITECH ERROR] SSD1306 Allocation Failed.");
    for(;;);
  }

  display.clearDisplay();
  renderOledSplash("ZARITECH RADAR", "BOOT COMPLETE", "System Standby OK");
  delay(1200);
}

void loop() {
  // Execute Precision Sonic Pulse Emission (Time-of-Flight Mapping)
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  // Compute absolute dynamic metric value in centimeters
  int distanceCm = duration * 0.034 / 2;

  // Track Dynamic Acoustic Radar Beats Based on Distance Density
  processRadarAlertBeats(distanceCm);

  // Refresh Local Graphical Canvas Frame Buffers
  refreshOledTelemetry(distanceCm);

  delay(60); // Stable processing yield delay
}

// Low-Latency Graphical Frame Buffer Renderer
void refreshOledTelemetry(int currentDistance) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  
  // Render Zaritech Decorative UI Header Bar
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("ZARITECH SPATIAL HUD");
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);
  
  // Render Computed Spatial Metrics
  display.setCursor(0, 20);
  display.print("METRIC: SPATIAL RADAR");
  
  display.setTextSize(2);
  display.setCursor(16, 36);
  if (currentDistance > 150 || currentDistance <= 0) {
    display.println("OUT RANGE");
  } else {
    display.print(currentDistance);
    display.println(" cm");
  }
  
  display.display();
}

// Adaptive Variable Frequency Acoustic Notification Engine
void processRadarAlertBeats(int distance) {
  if (distance > 0 && distance <= 15) { // Critical Close Proximity Array
    digitalWrite(ledGreen, LOW); digitalWrite(ledYellow, LOW); digitalWrite(ledRed, HIGH);
    digitalWrite(buzzerPin, HIGH); delay(30); digitalWrite(buzzerPin, LOW);
  } 
  else if (distance > 15 && distance <= 40) { // Warning Boundary Zone
    digitalWrite(ledGreen, LOW); digitalWrite(ledYellow, HIGH); digitalWrite(ledRed, LOW);
    digitalWrite(buzzerPin, HIGH); delay(30); digitalWrite(buzzerPin, LOW); delay(distance * 5);
  } 
  else if (distance > 40 && distance <= 80) { // Safe Range Zone
    digitalWrite(ledGreen, HIGH); digitalWrite(ledYellow, LOW); digitalWrite(ledRed, LOW);
    digitalWrite(buzzerPin, LOW);
  } 
  else { // Safe Idle Baseline
    digitalWrite(ledGreen, LOW); digitalWrite(ledYellow, LOW); digitalWrite(ledRed, LOW);
    digitalWrite(buzzerPin, LOW);
  }
}

void renderOledSplash(const char* title, const char* middle, const char* footer) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 15); display.println(title);
  display.setCursor(0, 32); display.println(middle);
  display.setCursor(0, 50); display.println(footer);
  display.display();
}
