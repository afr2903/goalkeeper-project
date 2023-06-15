#include "Mechanism.h"

Mechanism::Mechanism(){
    pinMode(mMotor.pinPwm, OUTPUT);
    pinMode(mMotor.pinA, OUTPUT);
    pinMode(mMotor.pinB, OUTPUT);

    pinMode(vrY, INPUT);

    pinMode(rightLimit, INPUT_PULLUP);
    pinMode(leftLimit, INPUT_PULLUP);
}

void Mechanism::update(bool autoMode, int xPos){
    if( millis() - lastTime < 10 )
        return;

    int joy = analogRead(vrY);
    if( joy > 620 || joy < 420){
        int error = joy - 520;
        setPWM( error * manual_kp );
    } else {
        if(autoMode){
            if( (xPos < 165 && xPos > 150) || xPos == 500){
                stop();
            } else {
                int error = xPos - 158;
                auto_integral += error;
                float pid = error * auto_kp + auto_integral * auto_ki;
                setPWM( pid );
            }
        } else {
            if( joy < 620 && joy > 420){
                stop();
            } else {
                int error = joy - 520;
                setPWM( error * manual_kp );
            }
        }
    }

    //estimate position
    if(isLeftLimit){
        estimatedPosition = 0;
    } else if(isRightLimit){
        estimatedPosition = 100;
    } else  {
        estimatedPosition += pwm * 0.0001;
    }
    //Serial.print("estimatedPosition: ");
    //Serial.println(estimatedPosition);
    lastTime = millis();
}

void Mechanism::setPWM(int pwm){
    int realPwm = min( max( abs(pwm), 50 ) , 255 );
    bool dir = pwm > 0;
    this->pwm = realPwm * (dir ? 1 : -1);
    if( (dir && isRightLimit) || (!dir && isLeftLimit) ){
        stop();
        return;
    }
    if(dir){
        digitalWrite(mMotor.pinA, HIGH);
        digitalWrite(mMotor.pinB, LOW);
    } else {
        digitalWrite(mMotor.pinA, LOW);
        digitalWrite(mMotor.pinB, HIGH);
    }
    analogWrite(mMotor.pinPwm, realPwm);
}

void Mechanism::rightLimitInterrupt(){
    stop();
    isRightLimit = !digitalRead(rightLimit);
}

void Mechanism::leftLimitInterrupt(){
    stop();
    isLeftLimit = !digitalRead(leftLimit);
}

void Mechanism::stop(){
    pwm = 0;
    digitalWrite(mMotor.pinA, LOW);
    digitalWrite(mMotor.pinB, LOW);
    analogWrite(mMotor.pinPwm, 0);
}
