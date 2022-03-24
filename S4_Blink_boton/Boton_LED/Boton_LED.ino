#define digitalReadPin 34
#define digitalWritePin 32

bool pinStatus;
//int pinStatus;

void setup() {
  Serial.begin(115200); 
  pinMode(digitalReadPin,INPUT);
  pinMode(digitalWritePin,OUTPUT);
}

void loop() {
  pinStatus = digitalRead(digitalReadPin); 
  Serial.println(pinStatus);

  //Una subrutina que encienda el LED si el botón esta presionado
  //Si no esta presionado, que lo apague
  //------
  //if(pinStatus==1){    
  if(pinStatus){    //pinStatus es true si el boton esta apretado
    digitalWrite(digitalWritePin,HIGH);
  } 
  else{
    digitalWrite(digitalWritePin,LOW);
  }
  //------
}
