/*
  Tutorial 2 - Ejemplo 1
  Implementación de un servidor de echo en puerto serie. Se
  reenvia por puerto serie lo que se lea por el mismo.
 
  Taller de uControladores ESIBot 2013
*/

void setup() {
  // inicializamos el puerto serie a 9600bps:
  Serial.begin(9600);
}

// variables que cambiarán:
int inByte = 0;

void loop() {
  if (Serial.available() > 0) {       // comprobamos si hay algún caracter recibido
    inByte = Serial.read();           // leemos un byte y lo almacenamos en una variable
    Serial.write(inByte);             // enviamos la variable por el puerto serie
  }
}