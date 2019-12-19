#ifndef SMART_RC_CAR_BLUETOOTH_H
#define SMART_RC_CAR_BLUETOOTH_H

#define X_AXIS_CMD_CHAR 'x'
#define Y_AXIS_CMD_CHAR 'y'
#define BUTTON_PRESSED_CMD_CHAR 'b'
#define CMD_SEPARATOR_CHAR ':'
#define BUTTON_PRESSED_TRUE_CHAR '1'

class Bluetooth {
    private:
        Stream &_SerialStream;
        float _xAxis;
        float _yAxis;
        bool _pressedValue;
        const int _statePin;

    public:
        Bluetooth(HardwareSerial &SerialStream, const int statePin, const unsigned int baudRate = 38400);

        // Receiver
        bool IsDataUpdated();
        float GetXAxis();
        float GetYAxis();
        bool GetPressedValue();

        // Transmitter
        void SendXAxis(float value);
        void SendYAxis(float value);
        void SendPressedValue(bool value);

        // Receiver & Transmitter
        bool IsConnected();
};


#endif //SMART_RC_CAR_BLUETOOTH_H
