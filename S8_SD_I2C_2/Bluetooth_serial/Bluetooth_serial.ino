#include <Adafruit_BME280.h>
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

const int LED_SENSOR = 32;
const int LED_BT = 33;


const int PHOTO = 34;

Adafruit_BME280 bme;
char payload[50]; //Datos que se envia an serial y Bluetooth

BluetoothSerial SerialBT;
boolean confirmRequestPending = true;


void BTConfirmRequestCallback(uint32_t numVal)
{
  confirmRequestPending = true;
  Serial.println(numVal);
  Serial.println("Do you consent?");
}

void BTAuthCompleteCallback(boolean success)
{
  confirmRequestPending = false;
  if (success)
  {
    Serial.println("Pairing success!!");
  }
  else
  {
    Serial.println("Pairing failed, rejected by user!!");
  }
}


void setup() {
  Serial.begin(115200);
  bme.begin(0x76);

  pinMode(LED_SENSOR,OUTPUT);
  pinMode(LED_BT,OUTPUT);

  //Autenticacion con SSP
  SerialBT.enableSSP();
  SerialBT.onConfirmRequest(BTConfirmRequestCallback);
  SerialBT.onAuthComplete(BTAuthCompleteCallback);
  
  SerialBT.begin("Axolote_ESP32"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");


}

void loop() {
  if (confirmRequestPending)
  {
    if (Serial.available())
    {
      int dat = Serial.read();
      if (dat == 'Y' || dat == 'y')
      {
        SerialBT.confirmReply(true);
      }
      else
      {
        SerialBT.confirmReply(false);
      }
    }
  }
  else
  {    
  digitalWrite(LED_SENSOR,HIGH); //Prende cuando empiece a leer
  sprintf(payload,"%04d,%06.2f",analogRead(PHOTO),bme.readPressure()/100); //Parecido a .format de Python
  digitalWrite(LED_SENSOR,LOW); //Prende cuando empiece a leer

  digitalWrite(LED_BT,HIGH); //Prende cuando empiece a escribir
  Serial.println(payload); //Manda por serial lo que se va a escribir por Bluetooth
  SerialBT.println(payload); //Envía por BT
  digitalWrite(LED_BT,LOW); //Apaga el LED cuando termina 

  delay(500);
  } 

}
