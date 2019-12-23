#include <Arduino.h>
#include "UltraSonic.h"

#define TRIG_PIN 11
#define ECHO_PIN 12

UltraSonic *Sonar;

void setup() {
    Serial.begin(9600);
    while (!Serial); // wait until serial is ready

    Sonar = new UltraSonic(TRIG_PIN, ECHO_PIN);
}

void loop() {
    float distance = Sonar->GetDistanceCentimeters();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
}
