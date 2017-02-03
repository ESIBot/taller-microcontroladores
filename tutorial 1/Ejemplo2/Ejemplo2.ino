/*
  Tutorial 0 - Ejemplo 2
  Enciende un LED cuando se pulsa un botón.
 
  Taller de uControladores ESIBot 2013
*/

// las constantes no cambiarán. Aquí se usan para
// especificar los pines usados:
const int buttonPin = PUSH2;        // pin para el botón
const int ledPin =  GREEN_LED;      // pin para el LED

// variables que cambiarán:
int buttonState = 0;         // variable para leer el estado del botón

void setup() {
  // inicializamos el pin del LED como salida:
  pinMode(ledPin, OUTPUT);      
  // inicializamos el pin del botón como entrada con pull-up:
  pinMode(buttonPin, INPUT_PULLUP);     
}

void loop(){
  // leemos el valor del botón
  buttonState = digitalRead(buttonPin);

  // comprobamos si el botón está pulsado.
  // si no lo está, buttonState estará como HIGH (pull-up):
  if (buttonState == HIGH) {     
    // apagamos el LED:
    digitalWrite(ledPin, LOW);  
  } 
  else {
    // encendemos el LED:
    digitalWrite(ledPin, HIGH); 
  }
}