//motor tests
#define SPEED 200

struct motor{
    int pinPwm;
    int pinA;
    int pinB;
};

struct motor hp_test = {9, 8, 10};

void setup() {
    pinMode(hp_test.pinPwm, OUTPUT);
    pinMode(hp_test.pinA, OUTPUT);
    pinMode(hp_test.pinB, OUTPUT);
}

void loop() {
    analogWrite(hp_test.pinPwm, SPEED);
    
    digitalWrite(hp_test.pinA, HIGH);
    digitalWrite(hp_test.pinB, LOW);
    delay(1500);
    digitalWrite(hp_test.pinA, LOW);
    digitalWrite(hp_test.pinB, HIGH);
    delay(1000);
    digitalWrite(hp_test.pinA, LOW);
    digitalWrite(hp_test.pinB, LOW);
    delay(1000);


}
