#include <AWS_IOT.h>
#include <WiFi.h>

//Wifi & AWS Parameters
#define WIFI_SSID "Red del Mago HF" // SSID of your WIFI
#define WIFI_PASSWORD "2659512562" //your wifi password
#define CLIENT_ID "Axolote_ESP32_Aldo"// thing unique ID, this id should be unique among all things associated with your AWS account.
#define MQTT_TOPIC "$aws/things/Axolote_ESP32_Aldo/shadow/update" //topic for the MQTT data
#define AWS_HOST "a9zwczf1oqpq2-ats.iot.us-east-1.amazonaws.com" // your host for uploading data to AWS,

AWS_IOT aws;

char payload [300];
bool status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(115200);

  //Conexion WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
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
      while(1);
  }

}

void loop() {

  sprintf(payload,"%s","Hello World!");
  Serial.println("Publishing:- ");
  Serial.println(payload);

  while(!aws.publish(MQTT_TOPIC, payload) == 0){// publishes payload and returns 0 upon success. 
      Serial.print(".");
      delay(50);
  }
  Serial.println("Success!");   
   
  delay(1000);
}
