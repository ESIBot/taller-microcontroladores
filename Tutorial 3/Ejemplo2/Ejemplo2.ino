/*
Tutorial 3 - Ejemplo 2
Genera una melodía en nuestro buzzer pasivo cambiando la frecuencia del pulso PWM.
Taller de uControladores ESIBot 2013
*/
// al igual que en el anterior ejemplo
// usamos un define en lugar de una variable:
#define BUZZER P2_2
#define DO 262 // frecuencia para generar un DO
#define RE 294 // frecuencia de Re
#define MI 330 // frecuencia Mi
#define FA 350 // frecuencia para generar un FA
#define SOL 392 // frecuencia SOL
#define LA 440 // frecuencia para generar un LA
#define SI 494 // frecuencia del SI
#define DOL 530 // frecuendia Do sostenido
#define REL 570 //frecuencia Re sostenido
#define SILENCIO 0

//Si se define Cancion, suena cumple, si no está definica, suena la cucaracha
//#define CANCION

#ifdef CANCION

const int notes[]{ // tabla dónde guardamos la melodía cumple

DO, DO, RE, DO, FA, MI,

DO, DO, RE, DO, SOL, FA,

DO, DO, DOL, LA, FA, MI, RE,

SI, SI, LA, FA, SOL, FA}; // queremos reproducir

const int duration[]{ //duración de cada nota

400,400,500,500,500,600,

400,400,500,500,500,600,

400,400,500,500,500,500,600,

400,400,500,500,500,600};

#else

const int notes[]{ // tabla dónde guardamos la melodía cucaracha

DO, DO, DO, FA, LA,

DO, DO, DO, FA, LA,

FA, FA, MI, RE, RE, DO,

DO, DO, DO, MI, SOL,

DO, DO, DO, MI, SOL,

DOL, REL, DOL, SI, LA, SOL, FA}; // queremos reproducir

const int duration[]{ //duración de cada nota

200,200,200,400,400,

200,200,200,400,400,

200,200,200,200,200,400,

200,200,200,400,400,

200,200,200,400,400,

200,200,200,200,200,200,400};

#endif


void setup() {
pinMode(BUZZER, OUTPUT); // definimos el pin dónde está el buzzer
}
// variables que cambiarán
int pwmValue = 128; // para conseguir el 50% de ancho de pulso
int freq = 0;
int i = 0;

void loop() {
//En este bucle vamos recorriendo la tabla con las notas que
//tenemos guardados, manteniéndolas la duración elegida.
for(i = 0; i<sizeof(notes)/sizeof(int); i++){
analogFrequency(notes[i]);
analogWrite(BUZZER, pwmValue);
delay (duration[i]);

// Ahora paramos de reproducir esa nota durante un tiempo pequeño.
analogWrite(BUZZER, SILENCIO);
delay (10);
}
analogWrite(BUZZER, SILENCIO);
delay (2000);
}

