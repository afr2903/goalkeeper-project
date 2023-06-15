#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//motor
#define MANUAL_SPEED 255

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

// lcd
LiquidCrystal_I2C lcd(0x27, 16, 2); // importa libreria LiquidCrystal

int pinIN = 4;   // Crea Variable pinIN y la asocia al pin digital 8
int valorIN = 0; // Crea Variables con un valor inicial asociado
int contenido = 0;
bool goalDetected = false;
bool goalDelay = false;
unsigned long goalDetectedTime = 0;

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

    lcd.backlight();
    lcd.init(); // inicializa lcd en 16 columnas por 2 filas
    // entradas analógicas no requieren inicialización

    lcd.print("THE GAME STARTS"); // Imprime "RSLICING3D" sobre el LCD
    delay(500);                   // Espera 1 segundo
    lcd.setCursor(0, 1);          // Seteamos la ubicacion texto 0 linea 1 que sera escrita sobre el LCD
    delay(1000);

    lcd.print("FEEL YOUR LEAGUE"); // Imprime "IZMAEL MF" sobre el LCD
    delay(500);                    // Espera 1 segundo
    lcd.setCursor(0, 2);

    lcd.print("DETECTOR"); // Imprime DETECTOR" sobre el LCD
    delay(500);           // Espera 1 segundo
    lcd.setCursor(0, 1);   // Seteamos la ubicacion texto 0 linea 1 que sera escrita sobre el LCD
    delay(200);
    lcd.clear(); // Limpia la pantalla
    delay(300);

    lcd.setCursor(1, 0);     // Seteamos la ubicacion del texto 1, linea 0 que sera escrita sobre el LCD
    lcd.print("NUMBER OF "); // Imprime "CUENTA OBJETOS" sobre el LCD
    lcd.setCursor(2, 1);
    lcd.print("GOALS: ");
}

void loop() {
    int joy = analogRead(vrY);
    if( joy < 620 && joy > 420){
        stop();
    } else if( joy > 620){
        manualRight( joy );
    } else if( joy < 420){
        manualLeft( joy );
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

    //Serial.println(joy);
    valorIN = digitalRead(pinIN); // Realiza la lectura Digital del pin 8
    if (valorIN != 1 && !goalDetected){             // Si la lectura es 1 incremente el valor de contenido
        contenido++;
        goalDetected = true;
        while (digitalRead(pinIN) != 1){
            delay(100); // Realiza un Delay para estabilizar
        }
        lcd.setCursor(12, 1); // Ubicamos el cursor en la posicion 12 sobre la linea 1
        lcd.print(contenido); // Imprimimos el valor del contenido sobre dicha ubicacion
        delay(3000);
    }
    if( valorIN == 1 && goalDetected ){
        lcd.setCursor(12, 1); // Ubicamos el cursor en la posicion 12 sobre la linea 1
        lcd.print(contenido); // Imprimimos el valor del contenido sobre dicha ubicacion
        goalDelay = true;
        goalDetectedTime = millis();
    }
    if( goalDelay && goalDetectedTime + 3000 > millis() ){
        goalDelay = false;
        goalDetected = false;
    }

}

void manualRight(int joy){
    if(isRightLimit){
        stop();
        return;
    }
    //map joystick value to motor speed, 600-1023, 100-255
    int speed = map(joy, 620, 1015, 40, 255);
    analogWrite(mMotor.pinPwm, MANUAL_SPEED);
    digitalWrite(mMotor.pinA, HIGH);
    digitalWrite(mMotor.pinB, LOW);
    Serial.println(speed);
}

void manualLeft(int joy){
    if(isLeftLimit){
        stop();
        return;
    }
    //map joystick value to motor speed, 400-0, 100-255
    int speed = map(joy, 420, 10, 40, 255);
    analogWrite(mMotor.pinPwm, MANUAL_SPEED);
    digitalWrite(mMotor.pinA, LOW);
    digitalWrite(mMotor.pinB, HIGH);
    Serial.println(speed);
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