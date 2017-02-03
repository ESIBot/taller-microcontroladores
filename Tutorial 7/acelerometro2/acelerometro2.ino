// Incluimos la libreria Wire.h la cual implementa el protocolo I2C
#include <Wire.h>
#include "acelerometro2.h"

#define INTERRUPTPIN P2_3
#define ROJO P2_0
#define VERDE P2_1
#define AZUL P2_2

void setup()
{
  
  Serial.begin(9600); 
  Wire.begin();          //Iniciamos el bus I2C en modo maestro

  pinMode(AZUL, OUTPUT);
  pinMode(VERDE, OUTPUT);
  pinMode(ROJO, OUTPUT);
  
  digitalWrite(ROJO, LOW);
  digitalWrite(VERDE, LOW);
  digitalWrite(AZUL, LOW);

  pinMode(INTERRUPTPIN, INPUT);


  //Configuración de los tres registros que itnervienen en la detección de golpes
  write(ADXL345ADDRESS, DUR, 0x1F); // 625us/LSB
  write(ADXL345ADDRESS, THRESH_TAP, 48); // 62.5mg/LSB  <==> 3000mg/62.5mg = 48 LSB as datasheet suggestion
  write(ADXL345ADDRESS, TAP_AXES, 1);
  
  //Configuración de los registros referentes a interrupciones
  write(ADXL345ADDRESS, INT_MAP, 0); //Enviamos todas las interrupciones al pin INT1
  write(ADXL345ADDRESS, INT_ENABLE, 0b01000000); //Activamos la interrupción por detección de golpe simple

  //Configuración del control de energía
  write(ADXL345ADDRESS,POWER_CTL, POWER_CTL_VALUE); 
 
}

int contador = 0; //Va contando el numero de golpes
int color = 0;

uint8_t* p_buffer = NULL;

float xAxis;    //Variables que usaremos para imprimir el resultado con una escala mas intuitiva
float yAxis;
float zAxis;



void loop(){

  while (digitalRead(INTERRUPTPIN) == 0){
    
    xAxis = SCALE2G * ((p_buffer[1] << 8) | p_buffer[0]); //El acelerómetro almacena el valor de cada eje en dos bytes por lo que 
    yAxis = SCALE2G * ((p_buffer[3] << 8) | p_buffer[2]); //necesitamos hacer esto para tener el dato completo
    zAxis = SCALE2G * ((p_buffer[5] << 8) | p_buffer[4]);
  
    Serial.print("Aceleración:\t"); //Imprimimos los valores obtenidos
    Serial.print(xAxis);
    Serial.print("   ");   
    Serial.print(yAxis);
    Serial.print("   ");   
    Serial.println(zAxis);
 
   Serial.println(digitalRead(INTERRUPTPIN));
 
    delay(200);
  }
  
   Serial.println("*********");
   Serial.print("Numero de cambios: "); 
   Serial.println(contador);
  
  read(ADXL345ADDRESS, INT_SOURCE, 1);
  read(ADXL345ADDRESS, ACT_TAP_STATUS, 1);
  
  contador++;
  color = contador%3;
   
  digitalWrite(ROJO, LOW);
  digitalWrite(VERDE, LOW);
  digitalWrite(AZUL, LOW);
   
  if (color == 0){
    digitalWrite(ROJO, HIGH); 
  }else if (color == 1){
    digitalWrite(VERDE, HIGH);
  }else{
    digitalWrite(AZUL, HIGH);
  }
  
 }

/****************************** FUNCIONES *******************************/

void write(int slave_Address, int address, int data){
  
	Wire.beginTransmission(slave_Address); //Ponemos en el bus la dirección del dispositivo con el que nos quereos comunicar
	Wire.write(address);                   //Registro al que queremos acceder
	Wire.write(data);                      //Dato que queremos poner en el registro
	Wire.endTransmission();                //Terminar la transmisión
}



uint8_t* read(int slave_Address, int address, int length){
  
  uint8_t buffer[length];                   //Buffer donde iremos guardando los datos que recibamos
  
  Wire.beginTransmission(slave_Address);    //Dirección del dispositivo con el que nos queremos comunicar
  Wire.write(address);                      //Que registro al que queremos acceder
  Wire.endTransmission();                 
  
  Wire.beginTransmission(slave_Address);    //Start repetido
  Wire.requestFrom(slave_Address, length);  //Modo lectura y cuantos bytes queremos
  
  if(Wire.available() == length){         
    for(uint8_t i = 0; i < length; i++){    //Leemos cada byte y rellenamos el buffer
      buffer[i] = Wire.read();
    }
  }    
  Wire.endTransmission();                 

  return buffer;
}


