#include <AWS_IOT.h>
#include <WiFi.h>

#define RELAY_PIN 8

//------MODIFICAR CON TUS PARAMETROS
//Wifi & AWS Parameters
#define WIFI_SSID "nombre_de_mi_red" // SSID of your WIFI
#define WIFI_PASSWORD "_passw_de_mi_red" //your wifi password
#define CLIENT_ID "Axolote_ESP32_"// thing unique ID, this id should be unique among all things associated with your AWS account.
#define MQTT_TOPIC "$aws/things/Axolote_ESP32_/shadow/PWM" //topic for the MQTT data
#define AWS_HOST "a9zwczf1oqpq2-ats.iot.us-east-1.amazonaws.com" // your host for uploading data to AWS,

int rc;
char msgReceived[10];
char rcvdPayload [10];
AWS_IOT aws;


void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad){
  Serial.println("Cambiando estado del relevador.");
  digitalWrite(RELAY_PIN, atoi(payLoad));
}

void setup() {
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

}
