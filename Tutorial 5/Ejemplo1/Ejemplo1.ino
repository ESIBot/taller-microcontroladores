/*
  Tutorial 5 - Ejemplo 1
  Cambia un LED cuando se pulsa un botón mediante interrupción.
 
  Taller de uControladores ESIBot 2013
*/

// variables del tipo volatile para cambiarlas
// dentro de una interrupción:
volatile int count = 0;

void setup() {                
  pinMode(RED_LED, OUTPUT);          // RED_LED como salida
  digitalWrite(RED_LED, LOW);        // lo dejamos apagado inicialmente
  pinMode(GREEN_LED, OUTPUT);        // RED_LED como salida
  digitalWrite(GREEN_LED, LOW);        // lo dejamos apagado inicialmente
  
  pinMode(PUSH2, INPUT_PULLUP);      // botón como entrada con pull-up
  
  Serial.begin(9800);                // iniciamos el puerto serie
  Serial.println(count, DEC);        // imprimimos el valor del contador

  // asignamos al pin PUSH2 una función que se ejecutará
  // cuando se detecte un flanco de subida:
  attachInterrupt(PUSH2, func, FALLING);
}

// variables del programa principal no volatile:
int last_count = 0;
unsigned long time = 0;

void loop() {
   // código principal de nuestra aplicación:
   if (last_count != count) {     // solo cuando haya cambiado el contador
     Serial.println(count, DEC);  // imprimimos su valor por puerto serie
     last_count = count;          // y actualizamos la variable auxiliar
   }
   
  if (millis() > time) {
    P1OUT ^= bit(6);            // ejecutamos este bloque cada 100ms
    time += 100;                // sin bloquear el programa
  }
}

// rutina de atención a la interrupción para PUSH2:
void func() {
    P1OUT ^= bit(0);
    count++;
}
