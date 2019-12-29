#include <Arduino.h>
#include "Joystick.h"
#include "Bluetooth.h"

#define SLAVE_STATE_D_PIN 11
#define X_AXIS_A_PIN 0
#define Y_AXIS_A_PIN 1
#define PRESS_D_PIN 2
#define EMISSION_INTERVAL_MILLISECONDS 100

Bluetooth *Slave;
Joystick *Controller;

void setup() {
    Slave = new Bluetooth(Serial1, SLAVE_STATE_D_PIN);
    Controller = new Joystick(PRESS_D_PIN, X_AXIS_A_PIN, Y_AXIS_A_PIN);
}

void loop() {
    Slave->SendXAxis(Controller->GetXAxis());
    Slave->SendYAxis(Controller->GetYAxis());
    Slave->SendPressedValue(Controller->IsPressed());
    delay(EMISSION_INTERVAL_MILLISECONDS);
}
