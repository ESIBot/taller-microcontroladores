/*
  Tutorial 4 - Ejemplo 2
  Uso del termómetro interno del microcontrolador
  
  Taller de uControladores ESIBot 2013
*/

#define MUESTRAS 256

void setup() {

  pinMode(PUSH2, INPUT_PULLUP);     

  analogReference(INTERNAL1V5);  //Configurar el ADC para que use la referencia interna de 1.5V

  Serial.begin(9600);
  Serial.println("Thermometer");
  Serial.println("press PUSH2 to exit serial");    

}

long int temp = 0;       //almacenamos el valor leido de la temperatura
long int tempMedia = 0;  //ya que el termómetro es un dispositivo que genera una salida con mucho ruido
                         //lo leeremos varias veces y calcularemos la media para tener una medida mas precisa
long int numMuestras = 0;

void loop() {
  
  tempMedia = 0; //debemos poner a 0 la variable para borrar el resultado de la iteración anterior
 
  for(numMuestras = 0; numMuestras < MUESTRAS; numMuestras++){

    //TEMPSENSOR es un pin interno el cual está conectado al termómetro
    temp = ((uint32_t)analogRead(TEMPSENSOR)*27069 - 18169625) * 10 >> 16; //escalamos el valor que devuelve el ADC
                                                                           //La justificación de la fórmula está en el tema
    tempMedia += temp; //sumamos cada muestra
  }                                          
  
  tempMedia /= MUESTRAS; //dividimos por el número de muestras
    
  
  //al escalar hemos dejado la temperatura multiplicada por 10, hacemos esto para evitar en lo posible trabajar con float                                                                    
  Serial.print("Temperatura: ");  
  Serial.print(tempMedia/10, DEC);    //Primero imprimimos la parte entera
  Serial.print(".");              
  Serial.println(tempMedia%10, DEC);  //Y después el decimal


  if (digitalRead(PUSH2)==LOW) {  //Si se pulsa el botón debe acabar el programa
    Serial.println("exit"); 
    Serial.end();                 //Se cierra el puerto serie
    while(true);                  //Y se bloquea el micro de forma indefinida para que no repita la función loop
  }

  delay(300);

}
