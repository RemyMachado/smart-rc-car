#ifndef SMART_RC_CAR_WHEELSMOTORS_H
#define SMART_RC_CAR_WHEELSMOTORS_H

#define MIN_MOTOR_SPEED 120 // considering weight of the car
#define MAX_MOTOR_SPEED 255
#define DELAY_HALF_TURN_MAX_SPEED_MILLISECONDS 700

class WheelsMotors {
    private:
        /* ENABLE / SET SPEED */
        const int _enA; // right motors speed
        const int _enB; // left motors speed
        /* MOTORS DIRECTIONS */
        const int _in1; // right motors forward
        const int _in2; // right motors backward
        const int _in3; // left motors backward
        const int _in4; // left motors forward

    public:
        WheelsMotors(const int enA, const int enB,
                     const int in1, const int in2, const int in3, const int in4);
        void Forward(float speedPercent);
        void Backward(float speedPercent);
        void Stop();
        void HalfTurnDirLeft();
        void HalfTurnDirRight();
        void TurnLeft();
        void TurnRight();
        void TurnHalfLeft();
        void TurnHalfRight();
        void TurnQuarterLeft();
        void TurnQuarterRight();

    private:
        int ComputeSpeed(float speedPercent);
};


#endif //SMART_RC_CAR_WHEELSMOTORS_H
