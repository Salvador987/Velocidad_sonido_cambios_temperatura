/* Escrito por:

Hernández Hernández Lluvia
Cuadros Jiménez Veronica
Cortés Sánchez Josué
Acevedo Mazzoco Alejandro
Tavera Mosqueda Salvador
García Rodríguez Víctor Hugo

//// Descargar biblioteca DHT11 https://github.com/adafruit/DHT-sensor-library
 */


#include "DHT.h"          //Biblioteca para el sensor de humedad y tmperatura DHT 11
#define DHTPIN 2          //Define el pin por el que se recibirá la señal del DHT 11
#define DHTTYPE DHT11     //Se especifica el tipo exacto de sensor
DHT dht(DHTPIN, DHTTYPE); // 

float tiempo;           //Eco (Echo)
float distancia;        //Variable a calcular 
float velocidad;        //Variable a calcular
float velocidadAire;    //Variable a calcular
float temperatura;      //Variable a calcular

void setup() 
{
 Serial.begin(9600);
 dht.begin();
 pinMode(9,OUTPUT);   //Trigger del sensor ultrasonico SR-HC05
 pinMode(8,INPUT);    //Echo del sensor ultrasonico SR-HC05
 
}

void loop() 
{
  digitalWrite (9,LOW);       //Pulso bajo para asegurar que no exista una lectura de señal parasita
  delayMicroseconds(50);       //duración del pulso bajo de 50 microsegundos 
  digitalWrite(9,HIGH);       //Pulso en alto para activar el sensor ultrasonico
  delayMicroseconds(10);      //duración del pulso alto de 10 microsegundos  
  
  tiempo= pulseIn(8,HIGH);    // Lee el pulso de regreso qeu fue envíado por el pin 9, este el es el eco o regreso del sonido  

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
distancia= round(float(0.01715 * tiempo)); //calcula la distancia, necesaria para obtener la velocidad ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 
if(distancia >= 50.00 && distancia <= 55.20)
{
//Velocidad del sonido considerando una distancia fija en metros (0.50) y la velocidad depende del tiempoque tarda en regresar el pulso/////
velocidad = (2.0 * 0.50) / (tiempo / 1000000.0);////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


temperatura = dht.readTemperature(); // Almacena la temperatura obtenida por el sendor DHT11 en la variable temperatura 

velocidadAire=331.4+(0.6*temperatura); // Formula para calcular la velocidad del sonido cuando hay cambios de temperatura

//Imprime la velocidad del sonido a partir de  de la formula v=331.4+(0.6 x °C) /////////////////////////////////////////////////////////
  Serial.print("\t Velocidad calculada="); ///////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.print(velocidadAire,0);//////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.print( "m/s");///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  Serial.print("\t Distancia=");
  Serial.print(distancia);
  Serial.print( "cm");
//Imprime la temperatura del ambiente a partir de las lecturas obtenidas por el sendor DHT11//////////////////////////////////////////////////
  Serial.print("\t Temperatura=");////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.print(temperatura);//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.print( "°C");////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Imprime la velocidad del sonido teorica a partir las lecturas obtenidas por los sensores /////////////////////////////////////////////////////////
  Serial.print("\t Velocidad medida =");
  Serial.print(velocidad,0);
  Serial.println( "m/s");


  delay(1000); //////////// Pausa el programa en mili segundos(ms)  1s= 1000 ms
  }
   
}
