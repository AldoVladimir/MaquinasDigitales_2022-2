#include <BluetoothSerial.h>


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

const int PAYLOAD_SIZE = 50;
const int LED_BT = 33;
char payload[PAYLOAD_SIZE]; 


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
  pinMode(LED_BT,OUTPUT);
  
  //Autenticacion con SSP
  SerialBT.enableSSP();
  SerialBT.onConfirmRequest(BTConfirmRequestCallback);
  SerialBT.onAuthComplete(BTAuthCompleteCallback);
  
  SerialBT.begin("Axolote_ESP32"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  
}


void loop() {
  
   if (confirmRequestPending){
    if (Serial.available()){
      int dat = Serial.read();
      //int dat = 'y'; //Hardcoded paring aproval
      if (dat == 'Y' || dat == 'y'){     
        SerialBT.confirmReply(true);      
      }
      else{
        SerialBT.confirmReply(false);
      }
    }
  }
  else{   
  
      if (Serial.available()) {        
        Serial.readBytesUntil('\n',payload,PAYLOAD_SIZE);
        SerialBT.println(payload);
      }
      if (SerialBT.available()) { 
        SerialBT.readBytesUntil('\n',payload,PAYLOAD_SIZE);
        Serial.println(payload);
      }
      delay(20);
      
  } 

}
