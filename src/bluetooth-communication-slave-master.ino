#include <Arduino.h>

#define PC_BAUD_RATE 9600
#define BLUETOOTH_BAUD_RATE 38400

// Slave need to be BIND to Master ADDR using the AT mode.
// be sure to respect the following Serial connections during the board setup:

auto &ComputerSerial = Serial;
auto &SlaveSerial = Serial1;
auto &MasterSerial = Serial2;

String buffer;

void setup() {
    ComputerSerial.begin(PC_BAUD_RATE);
    while (!ComputerSerial); // wait until Serial is ready
    SlaveSerial.begin(BLUETOOTH_BAUD_RATE); // SLAVE
    while (!SlaveSerial);
    MasterSerial.begin(BLUETOOTH_BAUD_RATE); // MASTER
    while (!MasterSerial);
}

void loop() {
    if (ComputerSerial.available()) {
        buffer = ComputerSerial.readStringUntil('\n'); // read data sent from PC on the Mega board

        ComputerSerial.write("Slave sent:"); // echo to PC
        ComputerSerial.println(buffer.c_str());
        SlaveSerial.write(buffer.c_str(), buffer.length()); // write to slave (should forward to master)
    }

    if (MasterSerial.available()) {
        buffer = MasterSerial.readStringUntil('\n'); // read from master

        ComputerSerial.write("Master received:"); // write result to PC
        ComputerSerial.println(buffer.c_str());
    }
}
