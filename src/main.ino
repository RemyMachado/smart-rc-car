#include <Arduino.h>

void setup() {
    Serial.begin(9600);
    while (! Serial); // Wait until Serial is ready
    Serial.println("Hello world!");
}

void loop() {
}

