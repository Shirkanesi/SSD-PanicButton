#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int bright = 100;
bool emergencyState = false;
bool direct = true;

void updatePixel(){
  if(emergencyState == true){
    for(int i = 0; i < NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color(0,bright,0));
    }
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
    bright = 100;
  }
}

void setEmergency(bool emg){
  emergencyState = emg;
}
