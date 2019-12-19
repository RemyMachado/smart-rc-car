#include <Arduino.h>
#include "Bluetooth.h"

#define SLAVE_STATE_D_PIN 11
#define MASTER_STATE_D_PIN 10
#define PC_BAUD_RATE 9600

auto &ComputerSerial = Serial;
Bluetooth *Slave;
Bluetooth *Master;

void setup() {
    ComputerSerial.begin(PC_BAUD_RATE);
    while (!ComputerSerial); // wait until serial is ready
    Slave = new Bluetooth(Serial1, SLAVE_STATE_D_PIN);
    Master = new Bluetooth(Serial2, MASTER_STATE_D_PIN);
}

void loop() {
    ComputerSerial.println("Slave sent:"); // echo to PC

    float randomX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float randomY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float randomB = static_cast <float> (rand());

    bool randomBool = randomB > (RAND_MAX / 2);

    ComputerSerial.println(String(randomX).c_str()); // echo to PC
    ComputerSerial.println(String(randomY * -1).c_str()); // echo to PC
    ComputerSerial.println(String(randomBool).c_str()); // echo to PC
    Slave->SendXAxis(randomX);
    Slave->SendYAxis(randomY * -1);
    Slave->SendPressedValue(randomBool);


    if (Master->IsDataUpdated()) {
        ComputerSerial.write("Master received x:"); // write result to PC
        ComputerSerial.println(Master->GetXAxis());
        ComputerSerial.write("Master received y:"); // write result to PC
        ComputerSerial.println(Master->GetYAxis());
        ComputerSerial.write("Master received b:"); // write result to PC
        ComputerSerial.println(Master->GetPressedValue());
    }

    ComputerSerial.println("--------------------------------"); // echo to PC
}

