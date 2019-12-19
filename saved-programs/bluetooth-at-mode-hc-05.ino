#include <Arduino.h>

// To use AT mode with HC-05 module, you need to press the key/enable button while powering it.

void setup() {
    Serial.begin(9600);
    while (!Serial); // wait until Serial is ready
    Serial1.begin(38400); // Bluetooth baud rate
    while (!Serial1);
}

void loop() {
    if (Serial.available()) {
        Serial1.write(Serial.read());
    }

    if (Serial1.available()) {
        Serial.write(Serial1.read());
    }
}
