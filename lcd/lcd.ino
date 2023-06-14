/*#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
uint8_t clock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
uint8_t retarrow[8] = {	0x1,0x1,0x5,0x9,0x1f,0x8,0x4};

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd
  lcd.backlight();

  lcd.createChar(0, bell);
  lcd.createChar(1, note);
  lcd.createChar(2, clock);
  lcd.createChar(3, heart);
  lcd.createChar(4, duck);
  lcd.createChar(5, check);
  lcd.createChar(6, cross);
  lcd.createChar(7, retarrow);
  lcd.home();

  lcd.print("Hello world...");
  lcd.setCursor(0, 1);
  lcd.print(" i ");
  lcd.printByte(3);
  lcd.print(" arduinos!");
  delay(5000);
  displayKeyCodes();

}

// display all keycodes
void displayKeyCodes(void) {
  uint8_t i = 0;
  while (1) {
    lcd.clear();
    lcd.print("Codes 0x"); lcd.print(i, HEX);
    lcd.print("-0x"); lcd.print(i+15, HEX);
    lcd.setCursor(0, 1);
    for (int j=0; j<16; j++) {
      lcd.printByte(i+j);
    }
    i+=16;

    delay(4000);
  }
}

void loop()
{

}*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// #include <LiquidCrystal.h> // Incluye la Libreria LiquidCrystal

LiquidCrystal_I2C lcd(0x27, 16, 2); // importa libreria LiquidCrystal

int pinIN = 4;   // Crea Variable pinIN y la asocia al pin digital 8
int valorIN = 0; // Crea Variables con un valor inicial asociado
int contenido = 0;

void setup()
{
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

void loop()
{
  valorIN = digitalRead(pinIN); // Realiza la lectura Digital del pin 8
  if (valorIN != 1)             // Si la lectura es 1 incremente el valor de contenido
  {
    contenido++;
    while (digitalRead(pinIN) != 1)
    {
      delay(100); // Realiza un Delay para estabilizar
    }
    lcd.setCursor(12, 1); // Ubicamos el cursor en la posicion 12 sobre la linea 1
    lcd.print(contenido); // Imprimimos el valor del contenido sobre dicha ubicacion
    delay(3000);
  }
}