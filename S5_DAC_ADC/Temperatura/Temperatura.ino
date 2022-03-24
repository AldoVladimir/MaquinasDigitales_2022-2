const int TEMP_SENSOR = 15;
const int LED_PIN = 32;


void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN,OUTPUT);
}

void loop() {
  //Se esperan lecturas de "250"
  //Serial.println(analogRead(TEMP_SENSOR));
  
  //El número digital está ok
  //Queremos temperatura
  //Serial.println(analogRead(TEMP_SENSOR)*0.8); //milivolt
  //Serial.println(analogRead(TEMP_SENSOR)*0.8/10); //°C

  //Usando adc2celcius:
  Serial.println(adc2celcius(analogRead(TEMP_SENSOR)));
  
  delay(10);
}

//Hago una función que retorna un valor
float adc2celcius(float adc_value){
  return adc_value*0.08;
}
