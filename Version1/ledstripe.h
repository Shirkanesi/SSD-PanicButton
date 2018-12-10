#include <Adafruit_NeoPixel.h>

//Tell the friendly pixels, how many the are...
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

//set the initial brightness
int bright = INIT_BRIGHT;

//The direction of the fading animation. true is fading up and false is fading down. Changes over time
bool direct = true;

//There is no emergency, when the arduino gets started!
bool emergencyState = false;

//c counts the time since the last STATE_LED-blink.
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
    bright = INIT_BRIGHT;

  }

  //Keep track over the run-LED. It toggles every RUN_LED_LEN seconds.
  c++;
  if(c == RUN_LED_LEN*10){
    digitalWrite(RUN_LED, HIGH);
    delay(125);
    digitalWrite(RUN_LED, LOW);
    c = 0;
  }
}

//Set the emergency-state of the system
void setEmergency(bool emg){
  emergencyState = emg;
}
