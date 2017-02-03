/*
  Tutorial 9 - Ejemplo 1 RX
  Recibe por IR lo que envía el otro Launchpad.
 
  Taller de uControladores ESIBot 2013
*/

#include <IRremote.h>

int RECV_PIN = P2_3;

// al igual que en el tutorial 8 necesitamos
// 2 variables para poder leer desde el IR:
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // iniciamos el puerto serie para imprimir lo
  // que nos llegue por IR:
  Serial.begin(9600);
  irrecv.enableIRIn(); // iniciamos el receptor
}

void loop() {
  // en caso de que llegue algún código correcto
  // lo imprimimos por puerto serie como un char:
  if (irrecv.decode(&results)) {
    Serial.print((char)results.value);
    irrecv.resume(); // recibimos el siguiente código
  }
}