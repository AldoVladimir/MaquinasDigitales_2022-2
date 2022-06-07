const int relay = 8;
 
void setup(){
  pinMode(relay,OUTPUT);
}
 
void loop(){
  digitalWrite(relay,HIGH);
  delay(1000);
  digitalWrite(relay,LOW);
  delay(3000);
}
