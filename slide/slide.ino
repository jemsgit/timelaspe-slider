/*
 * Simple demo, should work with any driver board
 *
 * Connect STEP, DIR as indicated
 *
 * Copyright (C)2015-2017 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>

#define DIR 8
#define STEP 9
#define ENDSTOP 7
int stepDelay;


int endstopValue = 0;
bool forward = true;
float stepCount = 0;  // number of steps the motor has taken

void setup() {
    pinMode(ENDSTOP, INPUT);
    pinMode(STEP, OUTPUT);
    pinMode(DIR, OUTPUT);
    digitalWrite(DIR, HIGH);
    Serial.begin(9600);
}

void simpleMove(int steps,int interval) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP, HIGH);
    digitalWrite(STEP, LOW);
    delay(interval);
  }
}

void loop() {
  int val = analogRead(A0);
  
  int stepDelay = map(val, 0, 1023, 1, 20);
  int stoper = digitalRead(ENDSTOP);
  if(stepCount <= 0) {
    forward = true;
    digitalWrite(DIR, LOW);
  }
  if(stoper < 1) {
    forward = false;
    digitalWrite(DIR, HIGH);
  }
  if (stepDelay > 0) {
    Serial.println(stepCount);
    Serial.println(stepDelay);
    simpleMove(20, stepDelay);
    if(forward) {
      stepCount+=20;
    } else {
      stepCount-=20;
    }
  }
  
}
