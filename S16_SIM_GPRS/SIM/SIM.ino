const int RXD2 = 16;
const int TXD2 = 17;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600,SERIAL_8N1,RXD2,TXD2);

}

void loop() {  
  while (Serial2.available()){    
    Serial.print(Serial2.read());
  }

  while(Serial.available()){
    Serial2.write(Serial.read());
  }
  
  /*
  Serial2.readBytesUntil('\n',gps_payload,300);
  Serial.println(gps_payload);
  */
}
