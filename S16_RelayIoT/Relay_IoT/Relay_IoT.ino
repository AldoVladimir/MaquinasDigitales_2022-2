#include <AWS_IOT.h>
#include <WiFi.h>

#define RELAY_PIN 12

//------MODIFICAR CON TUS PARAMETROS
//Wifi & AWS Parameters
#define WIFI_SSID "Red del Mago HF" // SSID of your WIFI
#define WIFI_PASSWORD "2659512562" //your wifi password
#define CLIENT_ID "Axolote_ESP32_Aldo"// thing unique ID, this id should be unique among all things associated with your AWS account.
#define MQTT_TOPIC "$aws/things/Axolote_ESP32_Aldo/shadow/relay" //topic for the MQTT data
#define AWS_HOST "a9zwczf1oqpq2-ats.iot.us-east-1.amazonaws.com" // your host for uploading data to AWS,

int rc;
char msgReceived[10];
char rcvdPayload [10];
AWS_IOT aws;


void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad){

  if (atoi(payLoad)){digitalWrite(RELAY_PIN,HIGH);}
  else{digitalWrite(RELAY_PIN,LOW);}
  
}

void setup() {
  
  pinMode(RELAY_PIN,OUTPUT);
  Serial.begin(115200);

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


    //Suscripción topic MQTT
    do{
          rc = aws.subscribe(MQTT_TOPIC,mySubCallBackHandler);
          if(rc == 0){
              Serial.println("Subscribe Successfull");
              delay(100);              
          }

      }while(rc != 0);

}

void loop() {
  //delay(10);
}
