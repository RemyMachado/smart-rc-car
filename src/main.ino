#include <Arduino.h>
#include "Joystick.h"

const int X_AXIS_A_PIN = 0;
const int Y_AXIS_A_PIN = 1;
const int PRESS_D_PIN = 2;

void setup() {
    Serial.begin(9600);
    while (! Serial); // Wait until Serial is ready
    Serial.println("Hello world!");
}

void loop() {
    auto *joystick = new Joystick(PRESS_D_PIN, X_AXIS_A_PIN, Y_AXIS_A_PIN);

    while (true) {
        Serial.print("x:");
        Serial.println(joystick->GetXAxis());
        Serial.print("y:");
        Serial.println(joystick->GetYAxis());
        Serial.print("is pressed:");
        Serial.println(joystick->IsPressed());
        delay(100);
    }
}

