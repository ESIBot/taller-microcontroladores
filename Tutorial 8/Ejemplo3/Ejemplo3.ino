/*
  Tutorial 8 - Ejemplo 3
  Controla un led RGB desde un mando de control remoto infrarrojo
 
  Taller de uControladores ESIBot 2013
*/


#include <IRremote.h>
#include <IRremoteInt.h>

#define RED    P1_2
#define GREEN  P1_6
#define BLUE   P2_6
#define RECV   P1_0

#define R  0xF720DF
#define G  0xF7A05F
#define B  0xF7609F

#define ON 0xF7C03F
#define OFF 0xF740BF

#define REPEAT 0xFFFFFFFF

#define FLASH 0xF700D4

// para poder usar la librería necesitaremos 2 variables
// una que sería el objeto encargado de crear una instancia
// de la clase IRrecv y otro donde este objeto podrá guardar
// los datos y que será del tipo decode_results:
IRrecv irrecv(RECV);
decode_results results;


void setup() {
  // configuramos como salidas los pines del LED:
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  // ponemos a nivel bajo el LED:
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);
  
  irrecv.enableIRIn(); // iniciamos el receptor
}

void loop(){
	// comprobamos si se ha decodificado algún código:
    if (irrecv.decode(&results)) {
      irrecv.resume(); // activamos para recibir el siguiente código

	  // realizamos una acción según el código que recibamos:
      switch(results.value) {
        case R: digitalWrite(RED,HIGH);
                digitalWrite(GREEN,LOW);
                digitalWrite(BLUE,LOW);
                break;
        case G: digitalWrite(RED,LOW);
                digitalWrite(GREEN,HIGH);
                digitalWrite(BLUE,LOW);
                break;
        case B: digitalWrite(RED,LOW);
                digitalWrite(GREEN,LOW);
                digitalWrite(BLUE,HIGH);
                break;
        case ON:digitalWrite(RED,HIGH);
                digitalWrite(GREEN,HIGH);
                digitalWrite(BLUE,HIGH);
                break;
        case OFF:digitalWrite(RED,LOW);
                 digitalWrite(GREEN,LOW);
                 digitalWrite(BLUE,LOW);
                break;
        case FLASH:
                break;
        case REPEAT:
                break; 
        default:break;
      }
    }
}
