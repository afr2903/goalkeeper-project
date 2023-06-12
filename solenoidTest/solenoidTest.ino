
bool solenoidButtonPressed = false;

void setup() {
    pinMode(7, OUTPUT);
    pinMode(12, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop() {
    /*digitalWrite(7, HIGH);
    delay(2000);
    digitalWrite(7, LOW);
    delay(2000);
    */
   //avoid button bounce, and when button is pressed, solenoid is activated for 500ms
    if(digitalRead(12) == LOW && solenoidButtonPressed == false){
         solenoidButtonPressed = true;
         digitalWrite(13, HIGH);
         Serial.println("solenoid activated");
         delay(500);
         digitalWrite(13, LOW);
         Serial.println("solenoid deactivated");
    } else if(digitalRead(12) == HIGH){
         solenoidButtonPressed = false;
    }
}
