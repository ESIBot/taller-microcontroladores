/*
  Tutorial 6 - Ejemplo 1
  Uso básico de la pantalla por SPI.
 
  Taller de uControladores ESIBot 2013
*/

// incluimos el fichero externo de SPI:
#include "SPI.h"

// definimos algunos pines que vamos a necesitar:
#define PINDC   P2_3
#define PINBL   P2_1
#define PINRST  P2_4

// variables que no cambiarán:
const uint8_t  _commandLCD = 0x00;
const uint8_t  _dataLCD    = 0x01;

const uint8_t glyphs[3][15] = {
  // dibujo 1
  {0x00, 0x00, 0x70, 0x18, 0x7D,
  0xB6, 0xBC, 0x3C, 0xBC, 0xB6,
  0x7D, 0x18, 0x70, 0x00, 0x00},
  
  // dibujo 2
  {0x00, 0x00, 0x9C, 0xDE, 0x56,
  0x36, 0x5F, 0x5F, 0x5F, 0x36,
  0x56, 0xDE, 0x9C, 0x00, 0x00},
  
  // dibujo 3
  {0x00, 0x00, 0x98, 0x5C, 0xB6,
  0x5F, 0x5F, 0x5F, 0x5F, 0xB6,
  0x5C, 0x98, 0x00, 0x00, 0x00}
  };
  
void setup() {
  // configuramos como salida los pines básicos
  // los de SPI los configurará la librería SPI:
  pinMode(PINDC, OUTPUT);
  pinMode(PINBL, OUTPUT);
  pinMode(PINRST, OUTPUT);
  
  // configuramos el periférico SPI con
  // la configuración necesaria para la pantalla:
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);

  // encendemos la luz trasera:
  digitalWrite(PINBL, HIGH);

  // proceso de inicialización según datasheet de PDC8544:
  digitalWrite(PINDC, LOW);
  delay(30);
  digitalWrite(PINRST, LOW);
  delay(100);
  digitalWrite(PINRST, HIGH);
  writeSPI(_commandLCD, 0x21);
  writeSPI(_commandLCD, 0xc8);
  writeSPI(_commandLCD, 0x12);
  writeSPI(_commandLCD, 0x20);
  writeSPI(_commandLCD, 0x09);
  writeSPI(_commandLCD, 0x0c);
  delay(10);
  
  // cursor a la posición (0,0):
  writeSPI(_commandLCD, 0x40 | 0);  // x
  writeSPI(_commandLCD, 0x80 | 0);  // y
  
  // rellenamos todo con 0x00, es decir limpiamos:
  for (uint16_t i=0; i<6*84; i++) writeSPI(_dataLCD, 0x00);
}

void loop() {
  // rellenamos todo con 0x0F:
  for (uint16_t i=0; i<6*84; i++) {
    writeSPI(_dataLCD, 0x0F);
    delay(5);
  }
  
  // rellenamos todo con 0xF0:
  for (uint16_t i=0; i<6*84; i++) {
    writeSPI(_dataLCD, 0xF0);
    delay(5);
  }
  
  //  limpiamos la pantalla y rellenamos con dibujos
  for (uint16_t i=0; i<6*84; i++) writeSPI(_dataLCD, 0x00);
  for (uint16_t i=0; i<6; i++) {
    for(uint16_t k=0; k<5; k++) {
      for(uint16_t j=0; j<15; j++)
        writeSPI(_dataLCD, glyphs[i%3][j]);
      delay(100);
      writeSPI(_dataLCD, 0x00);
      if (k != 4) writeSPI(_dataLCD, 0x00);
    }
  }
  delay(3000);
}

// esta función nos servirá para enviar por SPI
// un comando o datos, según el valor del parámetro
// dataCommand:
void writeSPI(uint8_t dataCommand, uint8_t c) {
    digitalWrite(PINDC, dataCommand);
    SPI.transfer((char)c);
}