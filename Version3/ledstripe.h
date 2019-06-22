#include <Adafruit_NeoPixel.h>

//Tell the friendly pixels, how many the are...
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

//set the initial brightness
int bright = INIT_BRIGHT;
bool ledState = true;

bool emgLEDstate = true;

bool res = false;

//The direction of the fading animation. true is fading up and false is fading down. Changes over time
bool direct = true;

//There is no emergency, when the arduino gets started!
bool emergencyState = false;

//c counts the time since the last STATE_LED-blink.
int c = 0;

int runMult = 10;

void noPixel(){
  for(int i = 0; i < NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  //Show the pixels
  pixels.show();
}


void updatePixel(){
  //Is currently an emergency?
  if(emergencyState == true){
    res = false;
    //No time for fancy animation... I hope it's enough for you :-(
    for(int i = 0; i < NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color(bright, 0, 0));
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
    
    if(bright >= 250 || bright <= 110){
      direct = !direct;
    }  
    if(bright <= 130){
      digitalWrite(EMG_LED, HIGH);
      delay(175);
      digitalWrite(EMG_LED, LOW);
      delay(125);
      digitalWrite(EMG_LED, HIGH);
      delay(175);
      digitalWrite(EMG_LED, LOW);
    }
  }else{
    //Reset brightnes
    if(!res){
      res = true;
      bright = INIT_BRIGHT;
      noPixel();
      digitalWrite(EMG_LED, LOW);
    }
    //Keep track over the run-LED. It toggles every RUN_LED_LEN seconds.
    c++;
    if(c >= RUN_LED_LEN*runMult){
      digitalWrite(RUN_LED, HIGH);
      delay(125);
      digitalWrite(RUN_LED, LOW);
      c = 0;
    } 
  }
}

//Set the emergency-state of the system
void setEmergency(bool emg){
  emergencyState = emg;
}
