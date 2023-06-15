//pixy detect color calibration
#include "Pixy2.h"
#include "Solenoid.h"
#include "Mechanism.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Pixy2 pixy;
Solenoid mSolenoid;
Mechanism mMechanism;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int rightLimit = 3;
const int leftLimit = 2;

//detect objects of signature 1
bool ballDetected = false;
int ballWidth = 0;
int ballX = 0;

bool autoMode = false;
unsigned long currentTime = 0;
unsigned long pixyTimer = 0;

const int pinLcd = 4;
int count = 0;
int input = 0; 
int contenido = 0;
bool goalDetected = false;
bool goalDelay = false;
unsigned long goalDetectedTime = 0;

void setup() {
    Serial.begin(9600);
    pixy.init();
    pixy.setLamp(0, 0);
    pixy.setLED(0, 255, 0);
    pixy.ccc.getBlocks();
    Serial.println("pixy setup complete");

    attachInterrupt(digitalPinToInterrupt(rightLimit), rightLimitInterrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(leftLimit), leftLimitInterrupt, CHANGE);

    pinMode(11, INPUT);
    
    lcd.backlight();
    lcd.init(); // inicializa lcd en 16 columnas por 2 filas
    // entradas analógicas no requieren inicialización

    lcd.print("THE GAME STARTS"); // Imprime "RSLICING3D" sobre el LCD
    delay(500);                   // Espera 1 segundo
    lcd.setCursor(0, 1);          // Seteamos la ubicacion texto 0 linea 1 que sera escrita sobre el LCD
    delay(500);

    lcd.print("FEEL YOUR LEAGUE"); // Imprime "IZMAEL MF" sobre el LCD
    delay(500);                    // Espera 1 segundo
    lcd.setCursor(0, 2);
    lcd.clear(); // Limpia la pantalla

    lcd.setCursor(1, 0);     // Seteamos la ubicacion del texto 1, linea 0 que sera escrita sobre el LCD
    lcd.print("NUMBER OF "); // Imprime "CUENTA OBJETOS" sobre el LCD
    lcd.setCursor(2, 1);
    lcd.print("GOALS: ");
}

void loop() {
    autoMode = digitalRead(11);
    currentTime = millis();
    ballWidth = 0;
    ballX = 500;

    if( autoMode && currentTime - pixyTimer > 10){
        ballDetected = false;
        pixy.ccc.getBlocks();
        Serial.print("Detected ");
        Serial.println(pixy.ccc.numBlocks);
        if (pixy.ccc.numBlocks>0) {
            for (int i = 0; i < pixy.ccc.numBlocks; i++) {
                //save width and x position of the ball wich signature is 1 and width is the greater in this signature, search for the greatest width
                if( pixy.ccc.blocks[i].m_signature == 1 && pixy.ccc.blocks[i].m_width > ballWidth){
                    ballDetected = true;
                    ballWidth = pixy.ccc.blocks[i].m_width;
                    ballX = pixy.ccc.blocks[i].m_x;
                }
                /*Serial.print("  sig: ");
                Serial.print(pixy.ccc.blocks[i].m_signature);
                Serial.print("  width: ");
                Serial.print(pixy.ccc.blocks[i].m_width);
                Serial.print("  x: ");
                Serial.println(pixy.ccc.blocks[i].m_x);*/

            }
        }
        if(ballDetected){
            Serial.print("ball detected, width: ");
            Serial.print(ballWidth);
            Serial.print(" x: ");
            Serial.println(ballX);
        } else {
            Serial.println("ball not detected");
        }
        pixyTimer = currentTime;
    }

    mSolenoid.update(autoMode, ballWidth);
    mMechanism.update(autoMode, ballX);
    
    
    input = digitalRead(pinLcd);
    if (input != 1 && !goalDetected){             // Si la lectura es 1 incremente el valor de contenido
        count++;
        goalDetected = true;
    }
    if( input == 1 && goalDetected ){
        lcd.setCursor(12, 1); // Ubicamos el cursor en la posicion 12 sobre la linea 1
        lcd.print(count); // Imprimimos el valor del contenido sobre dicha ubicacion
        goalDelay = true;
        goalDetectedTime = currentTime;
    }
    if( goalDelay && (goalDetectedTime + 5000 > currentTime) ){
        goalDelay = false;
        goalDetected = false;
    }
}

void rightLimitInterrupt(){
    mMechanism.rightLimitInterrupt();
}

void leftLimitInterrupt(){
    mMechanism.leftLimitInterrupt();
}