#include "Solenoid.h"

Solenoid::Solenoid(){
    pinMode(solenoidPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
}

void Solenoid::update(bool autoMode, int width){
    periodic( !digitalRead(buttonPin) );
}

void Solenoid::periodic(bool signal){
    switch (state){
        case AVAILABLE:
            if(signal == 1){
                activate();
                state = WAIT;
                timer = millis();
            }
            break;
        case WAIT:  //millis wait for 500
            if(millis() - timer > 50){
                deactivate();
                state = IDLE;
            }
            break;
        case IDLE:
            if(signal == 0){
                state = AVAILABLE;
            }
            break;
    }
}

void Solenoid::activate(){
    digitalWrite(solenoidPin, HIGH);
}

void Solenoid::deactivate(){
    digitalWrite(solenoidPin, LOW);
}