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

  Serial.begin(9600);
  
  //Config of pins
  pinMode(INPUT_PIN, INPUT_PULLUP);
  pinMode(TLK_PIN, OUTPUT);
  pinMode(RUN_LED, OUTPUT);

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
    digitalWrite(TLK_PIN, HIGH);    //  These lines
    delay(TIME_LEN);                //  are actually
    digitalWrite(TLK_PIN, LOW);     //  calling for
    delay(TIME_LEN);                //  help. They
    digitalWrite(TLK_PIN, HIGH);    //  are emulating
    delay(TIME_LEN);                //  some button
    digitalWrite(TLK_PIN, LOW);     //  presses. :P

    //Increase the loop counter
    buzzercount++;
    //Check, wheather is's time to beep
    if(buzzercount == BUZZ_FREQ){
      //Loop to trigger the buzzer BUZZER_COUNT times
      for(int i = 0; i<BUZZ_COUNT; i++){
        setBuzzer(true);
        delay(BUZZ_S_LEN);
        setBuzzer(false);
        delay((int)BUZZ_S_LEN*0.75);
      }
      buzzercount = 0;
    }

    //Wait some time. Without this, the arduino would always send an alarm, the walki takli gets confused. We don't want that...
    delay(BREAK_LEN);
  }else{
    //No emergency situation
    emergency = false;
    buzzercount = BUZZ_FREQ-1; //Hacky,  Hacky. Init to this value to make it beep, when the button gets pressed!
    //Not much to do here...
  }
  //update the state of the LED-Stripe. He wants some information too, so we should'nt be bad to him. He's beautiful
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
