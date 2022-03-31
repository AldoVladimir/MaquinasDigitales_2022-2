//#include <Adafruit_BMP085.h> //Biblioteca BMP180
///https://github.com/adafruit/Adafruit-BMP085-Library

#include <Adafruit_BME280.h>
#include <SD.h>

const int LED_READ = 32;
const int LED_WRITE = 33;

const int LIGHT_SENSOR = 34;

//Objetos de comunicación serial
Adafruit_BME280 bme; 
//Adafruit_BMP085 bmp; //Sensor barométrico
File myFile; //Objeto de clase File

char payload[50]; //Datos que se envia an serial y SD

void setup() {
  Serial.begin(115200);
  
  if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
  }
  //SD.begin(); //SD.begin(5)
  bme.begin(0x76);
  //bmp.begin(); //Si no se encuentra el dispositivo, usar I2C scanner

  pinMode(LED_READ,OUTPUT);
  pinMode(LED_WRITE,OUTPUT);



  digitalWrite(LED_READ,LOW);
  digitalWrite(LED_WRITE,LOW);
} 

void loop() {

  //Prende el LED cuando comienza la lectura. Apaga cuando termina
  digitalWrite(LED_READ,HIGH);
  
    //delay(100);
    sprintf(payload,"%06.2f,%04d",bme.readPressure()/100,analogRead(LIGHT_SENSOR));
    
  digitalWrite(LED_READ,LOW);



  //Prende LED cuando comienza escritura SD. Apaga cuando termina
  digitalWrite(LED_WRITE,HIGH);
  //delay(100);
    
    Serial.println(payload);

    myFile=SD.open("/Lecturas.csv",FILE_APPEND); //En ESP32 existe FILE_APPEND,FILE_WRIE y FILE_READ
    myFile.println(payload);
    myFile.close();
  
  digitalWrite(LED_WRITE,LOW);
  
  delay(10);
}
