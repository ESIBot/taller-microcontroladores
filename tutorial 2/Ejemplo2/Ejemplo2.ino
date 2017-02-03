/*
  Tutorial 2 - Ejemplo 1
  Uso de un bucle FOR para generar datos e imprimirlos
  por puerto serie con diferentes formatos.
 
  Taller de uControladores ESIBot 2013
*/

// variables que cambiarán:
int x = 0;

void setup() {
  // inicializamos el puerto serie a 9600bps:
  Serial.begin(9600);
}

void loop() {  
  // imprimimos las etiquetas
  Serial.print("WRITE");           // imprime texto de etiqueta
  Serial.print("\t");              // imprime una tabulación

  Serial.print("NORMAL");
  Serial.print("\t");

  Serial.print("DEC");  
  Serial.print("\t");      

  Serial.print("HEX"); 
  Serial.print("\t");   

  Serial.print("OCT");
  Serial.print("\t");

  Serial.println("BIN");           // imprime la última etiqueta con
                                   // retorno de carro

  for(x=32; x <= 126; x++){    // seleccionamos la parte imprimible de la tabla ASCII

    // imprimimos el dato en diferentes formatos:
    Serial.write(x);       // imprimimos en binario
    Serial.print("\t");    // imprime una tabulación

    Serial.print(x);       // imprimimos como decimal codificado en ASCII - igual que "DEC"
    Serial.print("\t");    // imprime una tabulación

    Serial.print(x, DEC);  // imprimimos como decimal codificado en ASCII
    Serial.print("\t");    // imprime una tabulación

    Serial.print(x, HEX);  // imprimimos como hexadecimal codificado en ASCII
    Serial.print("\t");    // imprime una tabulación

    Serial.print(x, OCT);  // imprimimos como octal codificado en ASCII
    Serial.print("\t");    // imprime una tabulación

    Serial.println(x, BIN);  // imprimimos como binario codificado en ASCII
                             // y añadimos un retorno de carro con "println"
							 
	// es importante tener en cuenta que la función Serial.print()
	// coloca los datos en el buffer de salida y retorna. Por tanto
	// el programa seguirá ejecutándose aunque los datos aún estén
	// esperando en el buffer y no se hayan enviado. Por eso colocamos
	// un delay, para no saturar el buffer de salida con datos.
    delay(200);
  }
  Serial.println();          // añadimos un retorno de carro al final de la tabla
}