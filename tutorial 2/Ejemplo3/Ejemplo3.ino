/*
  Tutorial 2 - Ejemplo 
  En este ejemplo se hace uso de la funci�n serialEvent() para
  detectar cuando ha llegado una linea completa. Tras esto se
  comprueba si es alg�n comando de los implementados y se
  ejecuta la acci�n programada en caso de que si lo sea.
 
  Taller de uControladores ESIBot 2013
*/

// variables que cambiar�n:
String inputString = "";         // una cadena que almacenar� lo que recibamos
boolean stringComplete = false;  // variable que indica si ha llegado una l�nea
int push = 0;    		 // variable para leer el estado del bot�n

void setup() {
  // configuramos los pines:
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  pinMode(PUSH2, INPUT_PULLUP);
  
  // inicializamos el puerto serie a 9600:
  Serial.begin(9600);
  // reservamos 50 bytes para inputString:
  inputString.reserve(50);
}

void loop() {
  // comprobamos si ha llegado una linea completa:
  if (stringComplete) {
    Serial.println("\n>>>"+inputString);  // imprimimos con >>> delante
	
    // comando LEDON:
    if(inputString.equalsIgnoreCase("LEDON")) {
      digitalWrite(GREEN_LED, HIGH);
      Serial.println("LED: ON");
      
    // comando LEDOFF:
	} else if (inputString.equalsIgnoreCase("LEDOFF")) {
      digitalWrite(GREEN_LED, LOW);
      Serial.println("LED: OFF"); 
    
    // comando READBUTTON:
    } else if (inputString.equalsIgnoreCase("READBUTTON")) {
      push = digitalRead(PUSH2);
      Serial.print("BOTON PULSADO: ");
      Serial.println((push==1)?"no":"si");
    
    // comando desconocido:
    } else {
      Serial.println("Comando no reconocido");
    }

    // borramos la cadena:
    inputString = "";
    stringComplete = false;
  }
}

/*
  Un SerialEvent tiene lugar cuando llegan nuevos datos
  en el pin RX de la UART. Esta funci�n se ejecuta entre
  cada iteraci�n del bucle loop(), por tanto usar funciones
  de delay() dentro del bucle puede hacer que la respuesta
  sea m�s lenta. M�ltiples bytes de datos pueden estar
  disponibles al ejecutar esta funci�n.
 */
void serialEvent() {
  while (Serial.available()) {
    // leemos el nuevo byte:
    char inChar = (char)Serial.read(); 
    
    // si el caracter de entrada es un \n, lo indicamos
    // en la variable para que el bucle principal pueda
    // hacer algo en consecuencia:
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      // en caso de que sea otro caracter, lo a�adimos inputString:
      inputString += inChar;
    }
  }
}