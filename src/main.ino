#include <Arduino.h>
#include "UltraSonic.h"
#include "ServoDirection.h"
#include "WheelsMotors.h"

#define TRIGGER_PIN PIN_A5
#define ECHO_PIN PIN_A4
#define SERVO_PIN 3
#define ENA 6
#define ENB 5
#define IN1 11
#define IN2 9
#define IN3 8
#define IN4 7

#define UNBLOCK_MANEUVER_INTERVAL 50

UltraSonic *Sonar;
ServoDirection *HeadDir;
WheelsMotors *Wheels;

long loopCount = 1;

void TakeBestDirection() {
    Wheels->Stop();
    HeadDir->Left();
    const float leftDistance = Sonar->GetDistanceCentimeters();

    HeadDir->HalfLeft();
    const float halfLeftDistance = Sonar->GetDistanceCentimeters();

    HeadDir->QuarterLeft();
    const float quarterLeftDistance = Sonar->GetDistanceCentimeters();

    HeadDir->QuarterRight();
    const float quarterRightDistance = Sonar->GetDistanceCentimeters();

    HeadDir->HalfRight();
    const float halfRightDistance = Sonar->GetDistanceCentimeters();

    HeadDir->Right();
    const float rightDistance = Sonar->GetDistanceCentimeters();

    HeadDir->Front(); // reset position

    if (leftDistance > halfLeftDistance &&
        leftDistance > quarterLeftDistance &&
        leftDistance > quarterRightDistance &&
        leftDistance > halfRightDistance &&
        leftDistance > rightDistance) {
        Wheels->TurnLeft();
    } else if (halfLeftDistance > leftDistance &&
               halfLeftDistance > quarterLeftDistance &&
               halfLeftDistance > quarterRightDistance &&
               halfLeftDistance > halfRightDistance &&
               halfLeftDistance > rightDistance) {
        Wheels->TurnHalfLeft();
    } else if (quarterLeftDistance > leftDistance &&
               quarterLeftDistance > halfLeftDistance &&
               quarterLeftDistance > quarterRightDistance &&
               quarterLeftDistance > halfRightDistance &&
               quarterLeftDistance > rightDistance) {
        Wheels->TurnQuarterLeft();
    } else if (quarterRightDistance > leftDistance &&
               quarterRightDistance > halfLeftDistance &&
               quarterRightDistance > quarterLeftDistance &&
               quarterRightDistance > halfRightDistance &&
               quarterRightDistance > rightDistance) {
        Wheels->TurnQuarterRight();
    } else if (halfRightDistance > leftDistance &&
               halfRightDistance > quarterLeftDistance &&
               halfRightDistance > quarterRightDistance &&
               halfRightDistance > halfLeftDistance &&
               halfRightDistance > rightDistance) {
        Wheels->TurnHalfRight();
    } else {
        Wheels->TurnRight();
    }
}

void setup() {
    Sonar = new UltraSonic(TRIGGER_PIN, ECHO_PIN);
    HeadDir = new ServoDirection(SERVO_PIN);
    Wheels = new WheelsMotors(ENA, ENB, IN1, IN2, IN3, IN4);
}

void loop() {
    const float distance = Sonar->GetDistanceCentimeters();

    /* DECISIONS TO TAKE */
    if (!(loopCount % UNBLOCK_MANEUVER_INTERVAL)) {
        // workaround allowing to get unstuck from unrecognized walls (often on an angle)
        Wheels->Backward(0.5);
        delay(500);
        TakeBestDirection();
    } else if (distance > 20) {
        Wheels->Forward(0.2);
        delay(100);
    } else {
        Wheels->Backward(0.5);
        delay(1000);
        TakeBestDirection();
    }
    ++loopCount;
}

