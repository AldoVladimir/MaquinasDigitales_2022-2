#include <TinyGPSPlus.h>


#include <AWS_IOT.h>
#include <WiFi.h>
TinyGPSPlus gps;

// The serial connection to the GPS device
const int RXD2 = 16;
const int TXD2 = 17;
static const uint32_t GPSBaud = 9600;


//------MODIFICAR CON TUS PARAMETROS
//Wifi & AWS Parameters
#define WIFI_SSID "Red del Mago HF" // SSID of your WIFI
#define WIFI_PASSWORD "2659512562" //your wifi password
#define CLIENT_ID "Axolote_ESP32_Aldo"// thing unique ID, this id should be unique among all things associated with your AWS account.
#define MQTT_TOPIC "$aws/things/Axolote_ESP32_Aldo/shadow/gps" //topic for the MQTT data
#define AWS_HOST "a9zwczf1oqpq2-ats.iot.us-east-1.amazonaws.com" // your host for uploading data to AWS,

AWS_IOT aws;
char payload [300];

void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600,SERIAL_8N1,RXD2,TXD2);

  //Conexion WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    while (!(WiFi.status() == WL_CONNECTED)) {
      Serial.print(".");
      delay(500);
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

}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (Serial2.available() > 0)
    if (gps.encode(Serial2.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
   Serial.println("Location: "); 
   if (gps.location.isValid()){
    //Lecturas en formato JSON
    sprintf(payload,"{"
    "\"deviceID\":\"AxoloteESP32_Aldo\","
    "\"location_lat\":%.8f,"
    "\"location_long\":%0.8f,"
    "\"Date_time\":\"%02d-%02d-%02d %02d:%02d:%02d \","  
    "}",gps.location.lat(),gps.location.lng(),
    gps.date.year(),gps.date.month(),gps.date.day(),
    gps.time.hour(),gps.time.minute(),gps.time.second()); 


    

    //AWS publish
    Serial.println("Publishing:- ");
    Serial.println(payload);
    
    while(!(aws.publish(MQTT_TOPIC, payload) == 0)){// publishes payload and returns 0 upon success. 
        Serial.print(".");
        delay(100);
    }
    Serial.println("Published!\n");

    
  }  
  
  else{
    Serial.println("INVALID");
  }


}
