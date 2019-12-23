#ifndef SMART_RC_CAR_ULTRASONIC_H
#define SMART_RC_CAR_ULTRASONIC_H

#define SPEED_OF_SOUND_METERS_PER_SECOND 343
#define SPEED_OF_SOUND_METERS_PER_MICROSECOND 0.000343
#define SPEED_OF_SOUND_CENTIMETERS_PER_MICROSECOND 0.0343

/* DESIGNED FOR ULTRA SONIC SENSOR HC-SR04 MODULE */

class UltraSonic {
    private:
        const int _triggerPin;
        const int _echoPin;

    public:
        UltraSonic(const int triggerPin, const int echoPin);
        float GetDistanceMeters();
        float GetDistanceCentimeters();

    private:
        unsigned long ComputeDurationMicroSeconds();
};


#endif //SMART_RC_CAR_ULTRASONIC_H
