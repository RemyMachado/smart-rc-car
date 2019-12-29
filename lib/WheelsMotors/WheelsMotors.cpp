#include <Arduino.h>
#include "WheelsMotors.h"

WheelsMotors::WheelsMotors(const int enA, const int enB, const int in1, const int in2, const int in3, const int in4) :
        _enA(enA), _enB(enB), _in1(in1), _in2(in2), _in3(in3), _in4(in4) {
    pinMode(this->_enA, OUTPUT);
    pinMode(this->_enB, OUTPUT);
    pinMode(this->_in1, OUTPUT);
    pinMode(this->_in2, OUTPUT);
    pinMode(this->_in3, OUTPUT);
    pinMode(this->_in4, OUTPUT);
}

void WheelsMotors::Forward(float speedPercent) {
    analogWrite(this->_enA, this->ComputeSpeed(speedPercent));
    analogWrite(this->_enB, this->ComputeSpeed(speedPercent));
    digitalWrite(this->_in1, HIGH);
    digitalWrite(this->_in2, LOW);
    digitalWrite(this->_in3, LOW);
    digitalWrite(this->_in4, HIGH);
}

void WheelsMotors::Backward(float speedPercent) {
    analogWrite(this->_enA, this->ComputeSpeed(speedPercent));
    analogWrite(this->_enB, this->ComputeSpeed(speedPercent));
    digitalWrite(this->_in1, LOW);
    digitalWrite(this->_in2, HIGH);
    digitalWrite(this->_in3, HIGH);
    digitalWrite(this->_in4, LOW);
}

void WheelsMotors::Stop() {
    digitalWrite(this->_enA, LOW);
    digitalWrite(this->_enB, LOW);
}

void WheelsMotors::HalfTurnDirLeft() {
    analogWrite(this->_enA, MAX_MOTOR_SPEED);
    analogWrite(this->_enB, MAX_MOTOR_SPEED);
    digitalWrite(this->_in1, HIGH);
    digitalWrite(this->_in2, LOW);
    digitalWrite(this->_in3, HIGH);
    digitalWrite(this->_in4, LOW);
    delay(DELAY_HALF_TURN_MAX_SPEED_MILLISECONDS);
    this->Stop();
}

void WheelsMotors::HalfTurnDirRight() {
    analogWrite(this->_enA, MAX_MOTOR_SPEED);
    analogWrite(this->_enB, MAX_MOTOR_SPEED);
    digitalWrite(this->_in1, LOW);
    digitalWrite(this->_in2, HIGH);
    digitalWrite(this->_in3, LOW);
    digitalWrite(this->_in4, HIGH);
    delay(DELAY_HALF_TURN_MAX_SPEED_MILLISECONDS);
    this->Stop();
}

void WheelsMotors::TurnLeft() {
    analogWrite(this->_enA, MAX_MOTOR_SPEED);
    analogWrite(this->_enB, MAX_MOTOR_SPEED);
    digitalWrite(this->_in1, HIGH);
    digitalWrite(this->_in2, LOW);
    digitalWrite(this->_in3, HIGH);
    digitalWrite(this->_in4, LOW);
    delay(DELAY_HALF_TURN_MAX_SPEED_MILLISECONDS / 2);
    this->Stop();
}

void WheelsMotors::TurnRight() {
    analogWrite(this->_enA, MAX_MOTOR_SPEED);
    analogWrite(this->_enB, MAX_MOTOR_SPEED);
    digitalWrite(this->_in1, LOW);
    digitalWrite(this->_in2, HIGH);
    digitalWrite(this->_in3, LOW);
    digitalWrite(this->_in4, HIGH);
    delay(DELAY_HALF_TURN_MAX_SPEED_MILLISECONDS / 2);
    this->Stop();
}

void WheelsMotors::TurnHalfLeft() {
    analogWrite(this->_enA, MAX_MOTOR_SPEED);
    analogWrite(this->_enB, MAX_MOTOR_SPEED);
    digitalWrite(this->_in1, HIGH);
    digitalWrite(this->_in2, LOW);
    digitalWrite(this->_in3, HIGH);
    digitalWrite(this->_in4, LOW);
    delay(DELAY_HALF_TURN_MAX_SPEED_MILLISECONDS / 4);
    this->Stop();
}

void WheelsMotors::TurnHalfRight() {
    analogWrite(this->_enA, MAX_MOTOR_SPEED);
    analogWrite(this->_enB, MAX_MOTOR_SPEED);
    digitalWrite(this->_in1, LOW);
    digitalWrite(this->_in2, HIGH);
    digitalWrite(this->_in3, LOW);
    digitalWrite(this->_in4, HIGH);
    delay(DELAY_HALF_TURN_MAX_SPEED_MILLISECONDS / 4);
    this->Stop();
}

void WheelsMotors::TurnQuarterLeft() {
    analogWrite(this->_enA, MAX_MOTOR_SPEED);
    analogWrite(this->_enB, MAX_MOTOR_SPEED);
    digitalWrite(this->_in1, HIGH);
    digitalWrite(this->_in2, LOW);
    digitalWrite(this->_in3, HIGH);
    digitalWrite(this->_in4, LOW);
    delay(DELAY_HALF_TURN_MAX_SPEED_MILLISECONDS / 8);
    this->Stop();
}

void WheelsMotors::TurnQuarterRight() {
    analogWrite(this->_enA, MAX_MOTOR_SPEED);
    analogWrite(this->_enB, MAX_MOTOR_SPEED);
    digitalWrite(this->_in1, LOW);
    digitalWrite(this->_in2, HIGH);
    digitalWrite(this->_in3, LOW);
    digitalWrite(this->_in4, HIGH);
    delay(DELAY_HALF_TURN_MAX_SPEED_MILLISECONDS / 8);
    this->Stop();
}

void WheelsMotors::TurnSlightLeft() {
    analogWrite(this->_enA, MAX_MOTOR_SPEED);
    analogWrite(this->_enB, MAX_MOTOR_SPEED);
    digitalWrite(this->_in1, HIGH);
    digitalWrite(this->_in2, LOW);
    digitalWrite(this->_in3, HIGH);
    digitalWrite(this->_in4, LOW);
    delay(DELAY_HALF_TURN_MAX_SPEED_MILLISECONDS / 30);
    this->Stop();
}

void WheelsMotors::TurnSlightRight() {
    analogWrite(this->_enA, MAX_MOTOR_SPEED);
    analogWrite(this->_enB, MAX_MOTOR_SPEED);
    digitalWrite(this->_in1, LOW);
    digitalWrite(this->_in2, HIGH);
    digitalWrite(this->_in3, LOW);
    digitalWrite(this->_in4, HIGH);
    delay(DELAY_HALF_TURN_MAX_SPEED_MILLISECONDS / 30);
    this->Stop();
}

int  WheelsMotors::ComputeSpeed(float speedPercent) {
    return speedPercent * (MAX_MOTOR_SPEED - MIN_MOTOR_SPEED) + MIN_MOTOR_SPEED;
}