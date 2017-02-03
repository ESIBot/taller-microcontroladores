/*
  Tutorial 4 - Ejemplo 1
  Uso de potenciómetro para ajustar el brillo de un led
  
  Taller de uControladores ESIBot 2013
*/


//definimos los pines que vamos a usar:
#define PINJOYSTICK  A1  
#define PINLED  P1_4


void setup() {
  pinMode(PINLED, OUTPUT);  
  //no necesitamos poner PINJOYSTICK como entrada ya que
  //la función analogRead() coloca el pin en un estado especial,
  //conectado al ADC
}


int joystickValue = 0; 
int pwmValue = 0;

void loop() {
  
  joystickValue = analogRead(PINJOYSTICK);  
  //leemos el valor del potenciometro  
  
  pwmValue = joystickValue/4;
  //lo escalamos para el pwm                                                                                                                                                                                  joystickValue/=4;
  
  analogWrite(PINLED, pwmValue); 
  //cambiamos el valor del PWM para el led 
  
  delay(100);
  
}
