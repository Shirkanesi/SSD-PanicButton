//Include necessary files.
#include "config.h"
#include <TimerOne.h>
#include "ledstripe.h"

//At the begin of the program, there is no emergency situation.
bool emergency = false;

//This value keeps track over the amount of loops, when device is in emergency
//Value is needed to have the buzzer beeping not all the time
int buzzercount;


void setup() {
  //For debugging use...
  Serial.begin(9600);
  
  //Config of pins
  pinMode(INPUT_PIN, INPUT_PULLUP);
  pinMode(TLK_PIN, INPUT_PULLUP);
  pinMode(RUN_LED, OUTPUT);
  pinMode(EMG_LED, OUTPUT);

  //Timer triggers every 0.1 seconds
  Timer1.initialize(0.1*1000000);
  Timer1.attachInterrupt(updatePixel);

  //Set buzzercount to a value
  buzzercount = BUZZ_FREQ-1; //Hacky,  Hacky. Init to this value to make it beep, when the button gets pressed!
  
  //Initialize the NeoPixel(WS2812B)-Stript
  pixels.begin();


}

void loop() {
  //Is the botton pressed? (Remember: We have a pull-up resistor, so check, if the pin gets some GND
  if(digitalRead(INPUT_PIN) == LOW){
    emergency = true;
    //Trigger the alarm
    pinMode(TLK_PIN, OUTPUT);
    digitalWrite(TLK_PIN, LOW);    
    delay(TIME_LEN);      
    pinMode(TLK_PIN, INPUT_PULLUP);    //We can't connect the walki talki directly to 5V. We have to use the (10k??) pull-up-resistor. 
    
    setEmergency(true);
  
    //Increase the loop counter
    buzzercount++;
    //Check, wheather it's time to beep
    if(buzzercount == BUZZ_FREQ){
      //Loop to trigger the buzzer BUZZ_COUNT times
      for(int i = 0; i<BUZZ_COUNT; i++){
        setBuzzer(true);
        delay(BUZZ_S_LEN);
        setBuzzer(false);
        delay(BUZZ_S_LEN);
      }
      buzzercount = 0;
    }
    
    //Wait some time. Without this, the arduino would always send an alarm, the walki takli gets confused. We don't want that...
    delay(4000);
  }else{
    //No emergency situation
    emergency = false;
    buzzercount = BUZZ_FREQ-1; //Hacky,  Hacky. Init to this value to make it beep, when the button gets pressed!
    bright = INIT_BRIGHT;
    noPixel();
    digitalWrite(EMG_LED, LOW);
    setEmergency(false);
  }
  //Update the state of the LED-Stripe. He wants some information too, so we should'nt be bad to him. Because he's beautiful
  setEmergency(emergency);
}

void setBuzzer(bool active){
  if(active){
    if(ACTIVE_BUZZ == 1){
      digitalWrite(BUZZER_PIN, HIGH);
    }else{
      tone(BUZZER_PIN, FREQUENCY * random(1, 4));
    }
  }else{
    if(ACTIVE_BUZZ == 1){
      digitalWrite(BUZZER_PIN, LOW);
    }else{
      noTone(BUZZER_PIN);
    }
  }
}
