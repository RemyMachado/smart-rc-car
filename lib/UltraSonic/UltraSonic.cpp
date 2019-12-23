#include <Arduino.h>
#include "UltraSonic.h"

UltraSonic::UltraSonic(const int triggerPin, const int echoPin) : _triggerPin(triggerPin), _echoPin(echoPin) {
    pinMode(this->_triggerPin, OUTPUT);
    pinMode(this->_echoPin, INPUT);
}

unsigned long UltraSonic::ComputeDurationMicroSeconds() {
    // clean state to ensure a good wave
    digitalWrite(this->_triggerPin, LOW);
    delayMicroseconds(2);

    // send wave
    digitalWrite(this->_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->_triggerPin, LOW);

    // micro seconds duration waited to receive echo wave
    return pulseIn(this->_echoPin, HIGH);
}


float UltraSonic::GetDistanceMeters() {
    return this->ComputeDurationMicroSeconds() * SPEED_OF_SOUND_METERS_PER_MICROSECOND / 2;
}

float UltraSonic::GetDistanceCentimeters() {
    return this->ComputeDurationMicroSeconds() * SPEED_OF_SOUND_CENTIMETERS_PER_MICROSECOND / 2;
}