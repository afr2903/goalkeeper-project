#ifndef Mechanism_h
#define Mechanism_h

#include "Arduino.h"

struct Motor{
    int pinPwm;
    int pinA;
    int pinB;
};

class Mechanism{
    private:
        Motor mMotor = {9, 8, 10};
        const int rightLimit = 3;
        const int leftLimit = 2;
        
        bool isRightLimit = false;
        bool isLeftLimit = false;

        const int vrY = A1;

        float auto_kp = 5.00;
        float auto_ki = 0.0001;
        float auto_kd = 0.0;
        float auto_integral = 0.0;
        float manual_kp = 0.53;
        int pwm = 0;
        int estimatedPosition = 0;
        unsigned long lastTime = 0;
    public:
        Mechanism();
        void update(bool autoMode, int xPos);
        void setPWM(int pwm);
        void rightLimitInterrupt();
        void leftLimitInterrupt();
        void stop();
};

#endif