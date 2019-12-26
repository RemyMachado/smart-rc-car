#ifndef SMART_RC_CAR_SERVODIRECTION_H
#define SMART_RC_CAR_SERVODIRECTION_H

#include <Servo.h>

class ServoDirection {
    private:
        int _angle;
        const int _defaultDelayMilliSeconds = 400;
        int _delayMilliSeconds;
        Servo _ServoHead;

    public:
        ServoDirection(const int servoPin, const int minPulse = 700, const int maxPulse = 2400);

        /* ROTATION */
        void Left();
        void HalfLeft();
        void QuarterLeft();
        void Front();
        void QuarterRight();
        void HalfRight();
        void Right();
        void ToDegree(const int degree);
        bool AddDegree(const int degree);
        bool SubtractDegree(const int degree);
        bool AddDegreeLeft(const int degree);
        bool AddDegreeRight(const int degree);

        /* DELAY */
        void SetDelayMilliSeconds(const int value);
        void ResetDelay();

    private:
        void UpdateAngle();
};


#endif //SMART_RC_CAR_SERVODIRECTION_H
