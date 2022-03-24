#include <math.h>

const int DAC_PIN = 25;
const int DAC_PIN_2 = 26;

int t=0; //Tiempo
float x; //Señal del DAC
String payload; //String que manda por serial

void setup() {
  Serial.begin(115200);  
}

void loop() {
  x=127*sin(2*PI*t/256)+128;
  t++;
  
  if(t>=256) {
    t=0;
  }

  //Señal sinusoidal solita
  //Serial.println(x); 

  //Con tiempo
  Serial.print(x); Serial.print('\t'); Serial.println(t); //Señal y tiempo

  //Sumando strings
  //payload= String(x)+"   "+String(t);
  //Serial.println(payload);

  //Escibir en el DAC
  dacWrite(DAC_PIN,x);
  dacWrite(DAC_PIN_2,t);
    
  delay(10);
}
