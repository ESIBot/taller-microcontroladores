/*
  Tutorial 6 - Ejemplo 2
  Uso avanzado de la pantalla por SPI. Ejemplo de cómo
  crear un juego como el clásico pong.
 
  Taller de uControladores ESIBot 2013
*/

// incluimos el fichero externo de SPI:
#include "SPI.h"

// definimos algunos pines que vamos a necesitar:
#define PINDC   P2_3
#define PINBL   P2_1
#define PINRST  P2_4
#define JOYSTICK A1

// variables que no cambiarán:
const uint8_t  _commandLCD = 0x00;
const uint8_t  _dataLCD    = 0x01;

// variables que cambiarán:
uint8_t player1Pos = 0;
uint16_t analog = 0;

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
  writeSPI(_commandLCD, 0x22);
  writeSPI(_commandLCD, 0x09);
  writeSPI(_commandLCD, 0x0c);
  delay(10);
  
  // cursor a la posición (0,0):
  setXY(0,0);
  
  // rellenamos todo con 0x00, es decir limpiamos:
  for (uint16_t i=0; i<6*84; i++) writeSPI(_dataLCD, 0x00);
}

void loop() {
  // leemos el valor de un eje del joystick
  // y lo escalamos al rango 0-35. Este valor
  // se usará para pintar la barra del jugador 1
  // en su posición correcta:
  analog = analogRead(JOYSTICK);
  player1Pos = map(analog, 0, 1023, 0, 35);
  printPlayer(player1Pos);
}

// esta función nos servirá para enviar por SPI
// un comando o datos, según el valor del parámetro
// dataCommand:
void writeSPI(uint8_t dataCommand, uint8_t c) {
    digitalWrite(PINDC, dataCommand);
    SPI.transfer((char)c);
}

// esta función envía por SPI el comando
// necesario para mover el cursor de columna
// y fila:
void setXY(uint8_t x, uint8_t y) {
  writeSPI(_commandLCD, 0x40 | y);  // y
  writeSPI(_commandLCD, 0x80 | x);  // x
}

// esta función se encarga de enviar por SPI
// valores para la primera columna completa
// de la pantalla:
void printPlayer(uint8_t pos) {
  // con la variable col representamos todos
  // los valores de la primera columna (48bits):
  uint64_t col = 0xFFF000000000;
  uint8_t temp = 0;

  // deplazamos el gráfico a su posición vertical:
  col = col>>(pos);
  
  // nos movemos al principio de la pantalla:
  setXY(0,0);
  
  // enviamos cada byte usando direccionamiento
  // vertical. Hay que recordar que el LSB de cada
  // byte representa el pixel más bajo de ese byte,
  // por eso llamamos a la función Bit_Reverse():
  for (uint8_t i = 0; i<6; i++) {
    temp = (uint8_t) 0xFF&(col>>(8*(5-i)));
    writeSPI(_dataLCD, Bit_Reverse(temp) );
  }
}

// esta función invierte el orden de los bits
// de un byte.
unsigned char Bit_Reverse( unsigned char x ) 
{ 
    x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa); 
    x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc); 
    x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0); 
    return x;    
}