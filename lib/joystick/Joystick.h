#ifndef SMART_RC_CAR_JOYSTICK_H
#define SMART_RC_CAR_JOYSTICK_H

class Joystick {
    private:
        int _pressDPin;
        int _xAxisAPin;
        int _yAxisAPin;

    public:
        Joystick(const int pressDPin, const int xAxisAPin, const int yAxisAPin);
        bool IsPressed();
        float GetXAxis();
        float GetYAxis();

    private:
        void InitializePinsMode();
        float AnalogToAxis(const int value);
};

#endif //SMART_RC_CAR_JOYSTICK_H
