#include "config.h"
#include <TimerOne.h>
#include "ledstripe.h"

//At the begin of the program, there is no emergency situation.
bool emergency = false;

void setup() {
  //Config of pins
  pinMode(INPUT_PIN, INPUT_PULLUP);
  pinMode(TLK_PIN, OUTPUT);
  pinMode(RUN_LED, OUTPUT);

  //Timer triggers every 0.1 seconds
  Timer1.initialize(0.1*1000000);
  Timer1.attachInterrupt(updatePixel);

  //Initialize the NeoPixel(WS2812B)-Stript
  pixels.begin();
}

void loop() {
  //Is the botton pressed? (Remember: We have a pull-up resistor, so check, if the pin gets some GND
  if(digitalRead(INPUT_PIN) == LOW){
    emergency = true;
    //Trigger the alarm
    digitalWrite(TLK_PIN, HIGH);
    delay(TIME_LEN);
    digitalWrite(TLK_PIN, LOW);
    delay(TIME_LEN);
    digitalWrite(TLK_PIN, HIGH);
    delay(TIME_LEN);
    digitalWrite(TLK_PIN, LOW);
    delay(BREAK_LEN);
  }else{
    //No emergency situation
    emergency = false;
  }
  setEmergency(emergency);
}
