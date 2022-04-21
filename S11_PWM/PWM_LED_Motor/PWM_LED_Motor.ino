const int PWM_PIN = 27;
const int TOUCH = 14;

int val = 0;
int t;
int  waveform;
void setup() {
  Serial.begin(115200);  
}

void loop() {
  /*
  if(Serial.available() > 0){
    Serial.read();
    waveform++;  
    if(waveform>=5) {
      waveform=0;
      
    }
    Serial.println(waveform);  
       
  }
  */


  if(touchRead(TOUCH) < 15){
     waveform++;  
     if(waveform>=5) {
        waveform=0;      
     }
     Serial.println(waveform);  
     delay(500);  
  }

  
  t++;  
  if(t>=256) {
    t=0;
  } 

  
  float freq=1;

  switch (waveform){
    case 0:
      val=255*0.5;
    break;
    
    case 1:
      val=255*0.8;
    break;

    case 2:
      val=255;
    break;
    
    case 3:
      val = t;
      delay(2); 
    break;

    case 4:    
      val = 127*sin(freq*(2*PI*t/256))+128;
    break;
  }

  
  analogWrite(PWM_PIN,255-val);
  delay(1);
  
}
