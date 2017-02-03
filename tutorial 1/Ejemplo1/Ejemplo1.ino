/*
  Tutorial 0 - Ejemplo 1
  Enciende alternativamente los leds rojo y verde en periodos de un segundo.
 
  Taller de uControladores ESIBot 2013
 */

void setup() {                
  // Inicializamos los leds como salidas:
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
}

void loop() {
  digitalWrite(RED_LED, HIGH);   // ponemos el led rojo on
  digitalWrite(GREEN_LED, LOW);  // ponemos el led verde off
  delay(1000);                   // esperamos un segundo
  digitalWrite(RED_LED, LOW);    // ponemos el led rojo off
  digitalWrite(GREEN_LED, HIGH); // ponemos el led verde on
  delay(1000);                   // esperamos un segundo
}