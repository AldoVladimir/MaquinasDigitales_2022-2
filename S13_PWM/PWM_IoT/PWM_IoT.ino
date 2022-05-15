#include <AWS_IOT.h>
#include <WiFi.h>

const int PWM_PIN = 12;
const int PWM_FREQ = 20000; //[Hz] //Frecuencia <1kHz poca eficiencia; >5kHz buena eficiencia
const int PWM_CHANNEL = 0;
const int PWM_RESOLUTION = 8; //Profundidad de bits

const int BUTTON = 4;

float t;
long  waveform = 0;
float dutyCycle;


//------MODIFICAR CON TUS PARAMETROS
//Wifi & AWS Parameters
#define WIFI_SSID "Red del Mago HF" // SSID of your WIFI
#define WIFI_PASSWORD "2659512562" //your wifi password
#define CLIENT_ID "Axolote_ESP32_Aldo"// thing unique ID, this id should be unique among all things associated with your AWS account.
#define MQTT_TOPIC "$aws/things/Axolote_ESP32_Aldo/shadow/accepted" //topic for the MQTT data
#define AWS_HOST "a9zwczf1oqpq2-ats.iot.us-east-1.amazonaws.com" // your host for uploading data to AWS,

int rc;
char msgReceived[10];
char rcvdPayload [10];
AWS_IOT aws;


void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{
  waveform = atoi(payLoad);
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON,INPUT_PULLDOWN);

  //Configuracion de PWM  
  ledcSetup(PWM_CHANNEL, PWM_FREQ , PWM_RESOLUTION); // Configuracion del canal PWM
  ledcAttachPin(PWM_PIN, PWM_CHANNEL); // Asignación del canal a un pin

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


  //Tiempo del ciclo
  t++;  
  if(t>=256) {
    t=0;
  } 


  //Menú de formas de onda disponibles
  switch (waveform){
    
    case 0:
     dutyCycle = 0;
    break;
    
    case 1:
     dutyCycle = 0.3;
    break;  
      
    case 2:
      dutyCycle = 0.5;
    break;
    
    case 3:
      dutyCycle = 0.8;
    break;

    case 4:
      dutyCycle = 1;
    break;

    //Graficar formas de onda en Desmos
    case 5:
      dutyCycle = (t+0.1)/256;
      delay(2.5);
    break;

    case 6:    
      dutyCycle = 0.5*sin(2*PI*t/256)+0.5;
      delay(0.5);
    break;

    case 7:    
      dutyCycle = pow(2.71828,((t/255)-1)*2);
      delay(4);
    break;
  }

  //Muestra forma de onda en serial plotter
  //Serial.println(dutyCycle*100);
  
  //Envia señal PWM al pin seleccionado
  ledcWrite(PWM_CHANNEL, dutyCycle*255);
  
}
