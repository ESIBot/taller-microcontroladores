/*
  Tutorial 6 - Ejemplo 3
  Uso de la librería de la pantalla.
 
  Taller de uControladores ESIBot 2013
*/

// incluimos las librerías necesarias
#include "SPI.h"
#include "LCD_5110_SPI.h"

// creamos un objeto del tipo LCD_5110_SPI
LCD_5110_SPI myScreen;

// variables que cambiarán
boolean	backlight = false;
uint8_t k = 0;

void setup() {
  // configuramos el periférico de SPI con
  // la configuración para la pantalla:
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);

  // especificamos los pines que queremos
  // usar para el resto de lines de la pantalla.
  // El orden es: CE, DC, RST, BL, PB
  myScreen = LCD_5110_SPI(P2_2, P2_3, P2_4, P2_1, PUSH2);
  
  myScreen.begin();                    // iniciamos la pantalla
  myScreen.setBacklight(backlight);    // encendemos la luz trasera
  myScreen.text(3, 2, "Iniciando");    // escribimos un texto en (3,2)
    
  delay(1000);                      // esperamos 1 segundo antes de
  myScreen.clear();                 // limpiar la pantalla completa
  myScreen.text(0, 5, "Apagar");    // y escribimos en (0,5)
}

void loop() {
  // el siguiente código actualiza el texto de (0,5)
  // en caso de que se pulse el botón
  if (myScreen.getButton()) {
      backlight = (backlight==0);
      myScreen.setFont(0);
      myScreen.text(0, 5, backlight ? "Encender" : "Apagar  ");
      myScreen.setBacklight(backlight);
  }
  
  // cambiamos a la fuente grande y escribimos según valga k
  myScreen.setFont(1);
  if (k==0)   myScreen.text(0, 1, "  HOLA  ");
  else if (k==8)   myScreen.text(0, 1, " MUNDO ");
  
  // aquí se hace una animación de un caracter por la pantalla
  myScreen.setFont(0);
  for (uint8_t i=0; i<14; i++) myScreen.text(i, 4, (i==k) ? "*" : " ");
  k ++;
  k %= 14;
  
  delay(200);
}