/*
  Tutorial 9 - Ejemplo 1 TX
  Envía por el emisor de IR lo que recibe por el puerto serie.
 
  Taller de uControladores ESIBot 2013
*/

#include <IRremote.h>

// en este caso usamos la misma librería, pero el objeto
// que necesitamos es diferente, se llama IRsend:
IRsend irsend;

void setup() {
  // iniciamos el puerto serie
  Serial.begin(9600);
}

// en esta variable almacenaremos temporalmente
// los bytes que recibamos por puerto serie:
int aux;

void loop() {
  // en caso de que recibamos un byte por puerto
  // serie lo enviamos por IR con protocolo Sony:
  if (Serial.available() > 0) {
    aux = Serial.read();
    irsend.sendSony((unsigned long)aux, 12); // enviamos como 12 bits
    delay(100);
  }
}