#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

int bright = 100;
bool emergencyState = false;
bool direct = true;

int c = 0;

void updatePixel(){
  //Is currently an emergency?
  if(emergencyState == true){
    //No time for fancy animation... I hope it's enough for you :-(
    for(int i = 0; i < NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color(0,bright,0));
    }
    //Show the pixels
    pixels.show();
    if(direct){
      //FadeUP
      bright += LED_STEP;  
    }else{
      //FadeDOWN
      bright -= LED_STEP;
    }
    
    if(bright >= 255 || bright < 100){
      direct = !direct;
    }  
  }else{
    //Reset brightnes
    bright = 100;

  }

  //Keep track over the run-LED. It toggles every RUN_LED_LEN seconds.
  c++;
  if(c == RUN_LED_LEN*10){
    digitalWrite(RUN_LED, HIGH);
    delay(125);
    digitalWrite(RUN_LED, LOW);   //Beeinflusst das hier irgendwas?
    c = 0;
  }
}

//Set the emergency-state of the system
void setEmergency(bool emg){
  emergencyState = emg;
}
