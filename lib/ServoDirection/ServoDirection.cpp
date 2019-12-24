#include <Arduino.h>
#include "ServoDirection.h"

ServoDirection::ServoDirection(const int servoPin, const int minPulse, const int maxPulse) {
    this->_ServoHead.attach(servoPin, minPulse, maxPulse);
    this->ResetDelay();
    this->Front();
}

void ServoDirection::Left() {
    this->_angle = 180;
    this->UpdateAngle();
}

void ServoDirection::HalfLeft() {
    this->_angle = 135;
    this->UpdateAngle();
}

void ServoDirection::Front() {
    this->_angle = 90;
    this->UpdateAngle();
}

void ServoDirection::HalfRight() {
    this->_angle = 45;
    this->UpdateAngle();
}

void ServoDirection::Right() {
    this->_angle = 0;
    this->UpdateAngle();
}

void ServoDirection::ToDegree(const int degree) {
    this->_angle = degree;
}

bool ServoDirection::AddDegree(const int degree) {
    if (this->_angle == 180) { // is already maximum value
        return false;
    }

    this->_angle += degree;

    if (this->_angle > 180) { // reached maximum value
        this->_angle = 180;
    }

    this->UpdateAngle();

    return this->_angle != 180;
}

bool ServoDirection::SubtractDegree(const int degree) {
    if (this->_angle == 0) { // is already minimum value
        return false;
    }

    this->_angle -= degree;

    if (this->_angle < 0) { // reached maximum value
        this->_angle = 0;
    }

    this->UpdateAngle();

    return this->_angle != 0;
}

bool ServoDirection::AddDegreeLeft(const int degree) {
    return this->AddDegree(degree);
}

bool ServoDirection::AddDegreeRight(const int degree) {
    return this->SubtractDegree(degree);
}

void ServoDirection::SetDelayMilliSeconds(const int value) {
    this->_delayMilliSeconds = value;
}

void ServoDirection::ResetDelay() {
    this->_delayMilliSeconds = this->_defaultDelayMilliSeconds;
}

void ServoDirection::UpdateAngle() {
    this->_ServoHead.write(this->_angle);
    delay(this->_delayMilliSeconds);
}
