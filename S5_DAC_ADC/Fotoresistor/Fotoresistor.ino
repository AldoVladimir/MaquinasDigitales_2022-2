const int analogReadPin = 34;
const int ledPin = 32;
const int THRESHOLD = 1000;
float luz;

//EL ADC tiene 0.8 mV de resolución
//EL DAC tiene 12 mV de resolución

void setup() {
  Serial.begin(115200);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  //Serial.println(analogRead(analogReadPin));
  
  // 1.- Encienda el LED si la lectura pasa un umbral THRESHOLD
  /*  
  Serial.println(luz);
  if (luz<=THRESHOLD){
    digitalWrite(ledPin,HIGH);
  }
  else{
    digitalWrite(ledPin,LOW);
  }
  */

  //Invoco la función en el loop
  luz = analogRead(analogReadPin);  
  ledSwitch(luz);

  //No es necesaria la variable "luz", solo necesitas el analog read
  //ledSwitch(analogRead(analogReadPin));
  
  delay(10);
}

// 2.- Convertir la actividad 1 en una función llamada "ledSwitch"
void ledSwitch(float value){
  
  Serial.println(value);
  if (value<=THRESHOLD){
    digitalWrite(ledPin,HIGH);
  }
  else{
    digitalWrite(ledPin,LOW);
  }
  
}
