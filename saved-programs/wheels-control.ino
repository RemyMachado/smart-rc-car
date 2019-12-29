#include <Arduino.h>
#include <Servo.h>
#include "UltraSonic.h"
#include "ServoDirection.h"
#include "WheelsMotors.h"

#define ENA 6
#define ENB 5
#define IN1 11
#define IN2 9
#define IN3 8
#define IN4 7

WheelsMotors *Wheels;

void setup() {
    Wheels = new WheelsMotors(ENA, ENB, IN1, IN2, IN3, IN4);
}

void loop() {
    Wheels->Forward(0.5);
    delay(2000);
    Wheels->Stop();
    delay(1000);

    Wheels->Backward(0.5);
    delay(2000);
    Wheels->Stop();
    delay(1000);

    Wheels->HalfTurnDirLeft();
    delay(1000);

    Wheels->HalfTurnDirRight();
    delay(1000);

    Wheels->TurnLeft();
    delay(1000);

    Wheels->TurnRight();
    delay(1000);

    while (true);
}

