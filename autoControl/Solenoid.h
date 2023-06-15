#ifndef Solenoid_h
#define Solenoid_h

#include "Arduino.h"

enum SolenoidState{
    AVAILABLE,
    WAIT,
    IDLE
};

class Solenoid{
    private:
        const int solenoidPin = 7;
        const int buttonPin = 6;
        bool buttonPressed = false;
        unsigned long timer = 0;
        SolenoidState state = AVAILABLE;
    public:
        Solenoid();
        void activate();
        void deactivate();
        void update(bool autoMode, int width = 0);
        void periodic(bool signal);
};

#endif