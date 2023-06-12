//motor
#define MANUAL_SPEED 150

struct motor{
    int pinPwm;
    int pinA;
    int pinB;
};

struct motor mMotor = {9, 8, 10};
const int rightLimit = 3;
const int leftLimit = 2;

bool isRightLimit = false;
bool isLeftLimit = false;

//joystick
const int vrY = A0;
const int button = 6;
bool buttonPressed = false;

//solenoid
const int solenoid = 7;

void setup() {
    Serial.begin(9600);
    pinMode(mMotor.pinPwm, OUTPUT);
    pinMode(mMotor.pinA, OUTPUT);
    pinMode(mMotor.pinB, OUTPUT);

    pinMode(vrY, INPUT);
    pinMode(button, INPUT_PULLUP);

    pinMode(rightLimit, INPUT_PULLUP);
    pinMode(leftLimit, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(rightLimit), rightLimitInterrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(leftLimit), leftLimitInterrupt, CHANGE);

    pinMode(solenoid, OUTPUT);

}

void loop() {
    if( analogRead(vrY) < 700 && analogRead(vrY) > 300){
        stop();
    } else if( analogRead(vrY) > 700){
        manualRight();
    } else if( analogRead(vrY) < 300){
        manualLeft();
    }

    if(digitalRead(button) == LOW && buttonPressed == false){
        buttonPressed = true;
        digitalWrite(solenoid, HIGH);
        Serial.println("solenoid activated");
        delay(500);
        digitalWrite(solenoid, LOW);
        Serial.println("solenoid deactivated");
    } else if(digitalRead(button) == HIGH){
        buttonPressed = false;
    }

    Serial.println(analogRead(vrY));
}

void manualRight(){
    if(isRightLimit){
        stop();
        return;
    }
    analogWrite(mMotor.pinPwm, MANUAL_SPEED);
    digitalWrite(mMotor.pinA, HIGH);
    digitalWrite(mMotor.pinB, LOW);
}

void manualLeft(){
    if(isLeftLimit){
        stop();
        return;
    }
    analogWrite(mMotor.pinPwm, MANUAL_SPEED);
    digitalWrite(mMotor.pinA, LOW);
    digitalWrite(mMotor.pinB, HIGH);
}

void stop(){
    analogWrite(mMotor.pinPwm, 0);
    digitalWrite(mMotor.pinA, 0);
    digitalWrite(mMotor.pinB, 0);
}

void rightLimitInterrupt(){
    stop();
    isRightLimit = !digitalRead(rightLimit);
    Serial.println("rightLimitInterrupt");
}

void leftLimitInterrupt(){
    stop();
    isLeftLimit = !digitalRead(leftLimit);
    Serial.println("leftLimitInterrupt");
}