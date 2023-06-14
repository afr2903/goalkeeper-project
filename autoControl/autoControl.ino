//pixy detect color calibration
#include "Pixy2.h"

Pixy2 pixy;

//detect objects of signature 1

void setup() {
    Serial.begin(9600);
    pixy.init();
    pixy.setLamp(1, 0);
    pixy.setLED(0, 255, 0);
    pixy.ccc.getBlocks();
    Serial.println("setup complete");
}

void loop() {
    pixy.ccc.getBlocks();
    if (pixy.ccc.numBlocks) {
        Serial.print("Detected ");
        Serial.println(pixy.ccc.numBlocks);
        for (int i = 0; i < pixy.ccc.numBlocks; i++) {
            Serial.print("  signature: ");
            Serial.print(pixy.ccc.blocks[i].m_signature);
            Serial.println();
        }
    }
    delay(50);
        
}
