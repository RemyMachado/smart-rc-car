#include <Arduino.h>
#include "Joystick.h"

Joystick::Joystick(const int pressDPin, const int xAxisAPin, const int yAxisAPin) {
    this->_pressDPin = pressDPin;
    this->_xAxisAPin = xAxisAPin;
    this->_yAxisAPin = yAxisAPin;
    this->InitializePinsMode();
}

bool Joystick::IsPressed() {
    return !digitalRead(this->_pressDPin);
}

float Joystick::GetXAxis() {
    return this->AnalogToAxis(analogRead(this->_xAxisAPin));
}

float Joystick::GetYAxis() {
    return this->AnalogToAxis(analogRead(this->_yAxisAPin));
}

void Joystick::InitializePinsMode() {
    pinMode(this->_pressDPin, INPUT_PULLUP);
    pinMode(this->_xAxisAPin, INPUT);
    pinMode(this->_yAxisAPin, INPUT);
}

float Joystick::AnalogToAxis(const int value) {
    return ((float)value - 512) / 512;
}

