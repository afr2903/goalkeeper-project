const int xStep = 3;
const int xDir = 2;
// señal para moverse 1.8, esta en el pin 2 //pin5, si es HIGH es un sentido y viceversa
const int sEnable = 8; // pin 8 activa y desactiva evita calentamiento
// int vel=0;

const int vry = A0;
const int vrx = A1;
const int joyButton = 5;

void setup(){
    Serial.begin(9600);
    pinMode(xStep, OUTPUT);
    pinMode(xDir, OUTPUT);
    pinMode(sEnable, OUTPUT);
    pinMode(vrx, INPUT);
    pinMode(vry, INPUT);
    digitalWrite(sEnable, HIGH); // HIGH desactiva el stepper
}

void loop(){
    /*digitalWrite(sEnable, LOW);
    digitalWrite(xDir, HIGH);
    pasos();
    digitalWrite(sEnable, HIGH); // desactivo stepper
    delay(1000);
    // subrutina pasos manda pulsos para moverse
    digitalWrite(sEnable, LOW);
    // activar stepper
    digitalWrite(xDir, LOW);
    // otro sentido
    pasos();
    // subrutina pasos manda pulsos para moverse
    digitalWrite(sEnable, HIGH); // desactivostepper
    delay(1000);*/

    Serial.print("x: ");
    Serial.print(analogRead(vrx));
    Serial.print(" y: ");
    Serial.println(analogRead(vry));

    if( analogRead(vrx) < 520 && analogRead(vrx) > 480){
        digitalWrite(sEnable, HIGH);
    } else if( analogRead(vrx) > 520){
        moveRight();
    } else if( analogRead(vrx) < 480){
        moveLeft();
    }
}

void pasos(){
    int vel = 2000;
    //test cycle 200 steps
    for (int i = 0; i < 2; i++){
        digitalWrite(xStep, HIGH);
        delayMicroseconds(vel);
        digitalWrite(xStep, LOW);
        delayMicroseconds(vel);
    }
}

void moveRight(){
    digitalWrite(sEnable, LOW);
    digitalWrite(xDir, HIGH);
    pasos();
}

void moveLeft(){
    digitalWrite(sEnable, LOW);
    digitalWrite(xDir, LOW);
    pasos();
}
// delay, mas pequeño mas rapido es el delay!!
// 100 pasos 180grados
// pulsos