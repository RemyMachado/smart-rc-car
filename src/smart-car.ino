#include <Arduino.h>
#include "Bluetooth.h"
#include "UltraSonic.h"
#include "ServoDirection.h"
#include "WheelsMotors.h"

#define TRIGGER_PIN PIN_A5
#define ECHO_PIN PIN_A4
#define MASTER_STATE_PIN 2
#define SERVO_PIN 3
#define ENA 6
#define ENB 5
#define IN1 11
#define IN2 9
#define IN3 8
#define IN4 7

#define UNBLOCK_MANEUVER_INTERVAL 50
#define MINIMUM_DISTANCE_CENTIMETERS 20
#define X_AXIS_MINIMUM_VALUE_TO_INTERPRET 0.1f
#define Y_AXIS_MINIMUM_VALUE_TO_INTERPRET 0.6f
#define AXIS_MAXIMUM_VALUE 1.0f

UltraSonic *Sonar;
ServoDirection *HeadDir;
WheelsMotors *Wheels;
Bluetooth *Master;

long loopCount = 1;
bool isAutoPilotMode = true;
bool isControllerButtonReleased = true; // used to debounce the received bluetooth data

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
    Master = new Bluetooth(Serial, MASTER_STATE_PIN);
}

void AutoPilot() {
    const float distance = Sonar->GetDistanceCentimeters();

    /* DECISIONS TO TAKE */
    if (!(loopCount % UNBLOCK_MANEUVER_INTERVAL)) {
        // workaround allowing to get unstuck from unrecognized walls (often on an angle)
        Wheels->Backward(0.5);
        delay(500);
        TakeBestDirection();
    } else if (distance > MINIMUM_DISTANCE_CENTIMETERS) {
        Wheels->Forward(0.2);
        delay(100);
    } else {
        Wheels->Backward(0.5);
        delay(1000);
        TakeBestDirection();
    }
    ++loopCount;
}

void RemoteControl() {
    const float valueX = Master->GetXAxis();
    const float valueY = Master->GetYAxis();

    /* FORWARD/BACKWARD */
    if (valueX < X_AXIS_MINIMUM_VALUE_TO_INTERPRET &&
        valueX > -X_AXIS_MINIMUM_VALUE_TO_INTERPRET) { // Joystick is probably in neutral position
        Wheels->Stop();
    } else if (valueX > X_AXIS_MINIMUM_VALUE_TO_INTERPRET) {
        Wheels->Forward(valueX);
    } else if (valueX < -X_AXIS_MINIMUM_VALUE_TO_INTERPRET) {
        Wheels->Backward(valueX * -1);
    }

    /* LEFT TURNS */
    if (valueY < -Y_AXIS_MINIMUM_VALUE_TO_INTERPRET && valueY >= -AXIS_MAXIMUM_VALUE) {
        Wheels->TurnSlightLeft();
    }

    /* RIGHT TURNS */
    if (valueY > Y_AXIS_MINIMUM_VALUE_TO_INTERPRET && valueY <= AXIS_MAXIMUM_VALUE) {
        Wheels->TurnSlightRight();
    }
}

void loop() {
    if (Master->IsDataUpdated()) { // check bluetooth reception
        if (Master->GetPressedValue()) {
            if (isControllerButtonReleased) {
                isAutoPilotMode = !isAutoPilotMode;
                isControllerButtonReleased = false;
            }
        } else {
            isControllerButtonReleased = true;
        }

        if (!isAutoPilotMode) {
            RemoteControl();
        }
    }

    if (isAutoPilotMode) {
        AutoPilot();
    }
}
