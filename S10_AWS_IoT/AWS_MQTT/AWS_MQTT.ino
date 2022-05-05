#include <AWS_IOT.h>
#include <WiFi.h>
#include <Adafruit_BME280.h>
//#include <Adafruit_BMP280.h> //Alumnos

//------MODIFICAR CON TUS PARAMETROS
//Wifi & AWS Parameters
#define WIFI_SSID "Red del Mago HF" // SSID of your WIFI
#define WIFI_PASSWORD "2659512562" //your wifi password
#define CLIENT_ID "Axolote_ESP32_Aldo"// thing unique ID, this id should be unique among all things associated with your AWS account.
#define MQTT_TOPIC "$aws/things/Axolote_ESP32_Aldo/shadow/update" //topic for the MQTT data
#define AWS_HOST "a9zwczf1oqpq2-ats.iot.us-east-1.amazonaws.com" // your host for uploading data to AWS,

#define WIFI_MAX 200 //Retries to connecto to WiFi
#define SERVICE_MAX 5 //Retries to publish data to AWS
#define DELAY_MINUTES 5 //Tiempo de retraso entre cada medicion

//------MODIFICAR CON TUS PARAMETROS
const int PHOTO = 34;
const int LED_CONNECTION = 26;
Adafruit_BME280 bme;
//Adafruit_BMP280 bme; //Alumnos

AWS_IOT aws;


char payload [300];
bool status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(115200);
  bme.begin(0x76);

  pinMode(LED_CONNECTION,OUTPUT);
  digitalWrite(LED_CONNECTION,LOW); 
}

void loop() {

  //Lecturas en formato JSON
  sprintf(payload,"{"
  "\"deviceID\":\"AxoloteESP32_Aldo\","
  "\"Press_hPa\":%06.2f,"
  "\"Luz_adim\":%04d"  
  "}",bme.readPressure()/100,analogRead(PHOTO)); 


  //Conexión y publicación
  digitalWrite(LED_CONNECTION,HIGH);  
    
    //Conexion WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    int count=0;
    while (!(WiFi.status() == WL_CONNECTED || count >=WIFI_MAX)) {
      Serial.print(".");
      count++;
      delay(500);
    }
     if(count<=WIFI_MAX){
      Serial.println("  ");
      Serial.println("Connected to WiFi\n");
     }
     else{
        Serial.println("Failed!\n");
        digitalWrite(LED_CONNECTION,LOW); 
        ESP.restart();
     }
    
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Connected to wifi");
  
    //Conexion AWS
    if(aws.connect(AWS_HOST,CLIENT_ID)== 0){// Connect to AWS using Host Address and Cliend ID
        Serial.println("Connected to AWS");
        delay(1000);
    }
    else{
        Serial.println("AWS connection failed, Check the HOST Address");
        Serial.println("Resetting");
        digitalWrite(LED_CONNECTION,LOW); 
        ESP.restart();      
    }   
      
    //AWS publish
    Serial.println("Publishing:- ");
    Serial.println(payload);
    count=0;
    while(!(aws.publish(MQTT_TOPIC, payload) == 0 || count >=SERVICE_MAX)){// publishes payload and returns 0 upon success. 
        Serial.print(".");
        count++;
        delay(100);
    }
    if(count<SERVICE_MAX){
        Serial.println("Published!\n");
     }
     // If failed to publish, reset MCU
     else{
        Serial.println("Failed!\n");
        Serial.println("Resetting");
        digitalWrite(LED_CONNECTION,LOW); 
        ESP.restart();
     }   

     
  digitalWrite(LED_CONNECTION,LOW); 
  
  delay(1000*60*DELAY_MINUTES);
  ESP.restart();
}
