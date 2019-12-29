#include <Arduino.h>
#include <Servo.h>
#include "UltraSonic.h"
#include "ServoDirection.h"

#define TRIGGER_PIN PIN_A5
#define ECHO_PIN PIN_A4

UltraSonic *Sonar;
ServoDirection *HeadDir;

void setup() {
    Serial.begin(9600);
    while(!Serial); // wait until serial is ready
    Sonar = new UltraSonic(TRIGGER_PIN, ECHO_PIN);
    HeadDir = new ServoDirection(3);
}

void loop() {
    HeadDir->Left();
    Serial.println(Sonar->GetDistanceCentimeters());
    HeadDir->HalfLeft();
    Serial.println(Sonar->GetDistanceCentimeters());
    HeadDir->Front();
    Serial.println(Sonar->GetDistanceCentimeters());
    HeadDir->HalfRight();
    Serial.println(Sonar->GetDistanceCentimeters());
    HeadDir->Right();
    Serial.println(Sonar->GetDistanceCentimeters());
    HeadDir->SetDelayMilliSeconds(15);
    while (HeadDir->AddDegreeLeft(10));
    HeadDir->ResetDelay();
    delay(1000);
}
