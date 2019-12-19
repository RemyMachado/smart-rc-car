#include <Arduino.h>
#include <HardwareSerial.h>
#include "Bluetooth.h"

Bluetooth::Bluetooth(HardwareSerial &SerialStream, const int statePin, const unsigned int baudRate) : _SerialStream(
        SerialStream),
                                                                                                      _xAxis(0.0f),
                                                                                                      _yAxis(0.0f),
                                                                                                      _pressedValue(
                                                                                                              false),
                                                                                                      _statePin(
                                                                                                              statePin) {
    pinMode(statePin, INPUT);
    SerialStream.begin(baudRate);
    while (!SerialStream); // wait until Serial is ready
}

bool Bluetooth::IsDataUpdated() {
    if (this->_SerialStream.available()) {
        String receivedData;

        while (this->_SerialStream.available()) {
            receivedData = _SerialStream.readStringUntil('\n');

            switch (receivedData[0]) {
                case X_AXIS_CMD_CHAR: // x:0.12 || x:-0.54
                    this->_xAxis = atof(receivedData.substring(2).c_str());
                    break;

                case Y_AXIS_CMD_CHAR:
                    this->_yAxis = atof(receivedData.substring(2).c_str());
                    break;

                case BUTTON_PRESSED_CMD_CHAR: // b:1 || b:0
                    this->_pressedValue = receivedData[2] == BUTTON_PRESSED_TRUE_CHAR;
                    break;

                default:
                    // Value not recognized
                    break;
            }
        }

        return true;
    }

    return false;
}

float Bluetooth::GetXAxis() {
    return this->_xAxis;
}

float Bluetooth::GetYAxis() {
    return this->_yAxis;
}

bool Bluetooth::GetPressedValue() {
    return this->_pressedValue;
}

void Bluetooth::SendXAxis(float value) {
    String payload = String(X_AXIS_CMD_CHAR);
    payload += CMD_SEPARATOR_CHAR;
    String convertedValue = String(value, 2);

    payload += convertedValue;
    payload += '\n';

    this->_SerialStream.write(payload.c_str());
}

void Bluetooth::SendYAxis(float value) {
    String payload = String(Y_AXIS_CMD_CHAR);
    payload += CMD_SEPARATOR_CHAR;
    String convertedValue = String(value, 2);

    payload += convertedValue;
    payload += '\n';

    this->_SerialStream.write(payload.c_str());
}

void Bluetooth::SendPressedValue(bool value) {
    String payload = String(BUTTON_PRESSED_CMD_CHAR);
    payload += CMD_SEPARATOR_CHAR;

    if (value) {
        payload += BUTTON_PRESSED_TRUE_CHAR;
    } else {
        payload += '0';
    }
    payload += '\n';

    this->_SerialStream.write(payload.c_str());
}

bool Bluetooth::IsConnected() {
    return digitalRead(_statePin);
}
