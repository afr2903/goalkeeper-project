//ultrasonic sensor test HCSR04

const int trigPin = 2;
const int echoPin = 3;
const int ledPin = 4;

void setup() {
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(ledPin, OUTPUT);
}

void loop() {
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
    Serial.print(distance);
    Serial.println(" cm");

    digitalWrite(ledPin, distance < 20 ? HIGH : LOW);

    delay(500);
}
