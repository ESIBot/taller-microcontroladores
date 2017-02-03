/*
  Tutorial 3 - Ejemplo 1
  Controla el brillo de los distintos colores básicos de una lámpara RGB
  (rojo, verde y azul).
 
  Taller de uControladores ESIBot 2013
*/


// usaremos definiciones en lugar de variables
// de esta forma no se usará memoria SRAM:
#define redPin 12
#define greenPin 13
#define bluePin 14

void setup()  {
  // configuramos como salidas los pines del LED RGB:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

} 

// variables que cambiarán:
int pwmValue = 0;	//variable que indicará el ancho de pulso, de
                          //0 a 255
void loop()  { 

  // en este bucle iremos aumentando el valor de pwmValue para
  // conseguir que el brillo de la lámpara aumente paulatinamente. El
  // paso es de cinco en cinco para que tarde menos en terminar:
  for (pwmValue = 0 ; pwmValue <= 255; pwmValue +=5) { 
    // vamos a escribir en el pin de nuestra lámpara RGB que 
    // corresponde al color rojo. Esto hará que empiece a brillar cada   
    // vez más fuerte dicho color.
    analogWrite(redPin, pwmValue); 	        
    delay(30);                            
  } 
    // hacemos lo mismo, pero al contrario. Ahora el rojo irá 
    // brillando cada vez menos hasta desaparecer.
  for (pwmValue = 255 ; pwmValue >= 0; pwmValue -=5) { 
    analogWrite(redPin, pwmValue);         
    delay(30);                            
  } 
  
  /**************** Repetimos para el color verde **********************/
  for (pwmValue = 0 ; pwmValue <= 255; pwmValue +=5) { 
    analogWrite(greenPin, pwmValue);         
    delay(30);                            
  }

  for (pwmValue = 255 ; pwmValue >= 0; pwmValue -=5) { 
    analogWrite(greenPin, pwmValue);         
    delay(30);                            
  } 
  
  /**************** Repetimos para el color azul ***********************/  
    for (pwmValue = 0 ; pwmValue <= 255; pwmValue +=5) { 
    analogWrite(bluePin, pwmValue);         
    delay(30);                            
  } 

  for (pwmValue = 255 ; pwmValue >= 0; pwmValue -=5) { 
    analogWrite(bluePin, pwmValue);         
    delay(30);                            
  }   
}
