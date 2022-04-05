#include <SD.h>
#include <Adafruit_BME280.h> //Alumnos es BMP280

File archivo;

const int LED_SENSOR = 33;
const int LED_SD = 32;
const int PHOTO= 34;

Adafruit_BME280 bmp; //Objeto BME280
//Adafruit_BMP280 bmp; //Objeto BMP280

char payload[50];

void setup() {
  Serial.begin(115200);
  SD.begin();
  
  pinMode(LED_SENSOR,OUTPUT);
  pinMode(LED_SD,OUTPUT);

  bmp.begin(0x76);
  
}

void loop() {

  digitalWrite(LED_SENSOR,HIGH); //Prende cuando empiece a leer
  sprintf(payload,"%04d,%06.2f",analogRead(PHOTO),bmp.readPressure()/100); //Parecido a .format de Python
  digitalWrite(LED_SENSOR,LOW); //Prende cuando empiece a leer

  
  digitalWrite(LED_SD,HIGH); //Prende cuando empiece a escribir
  Serial.println(payload); //Manda por serial lo que se va a escribir en la SD
  archivo = SD.open("/Luz_Presion.csv",FILE_APPEND); //Abre el archivo
  archivo.println(payload); //Escribe en el archivo
  archivo.close(); //Cierra el archivo
  digitalWrite(LED_SD,LOW); //Apaga el LED cuando termina 

  delay(500);
  
}
