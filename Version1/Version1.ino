#include "config.h"
#include <TimerOne.h>
#include "config.h"
#include "ledstripe.h"

bool emergency = false;

void setup() {
  pinMode(INPUT_PIN, INPUT_PULLUP);
  pinMode(TLK_PIN, OUTPUT);

  //Timer triggert alle 0.1 Sekunden
  Timer1.initialize(0.1*1000000);
  Timer1.attachInterrupt(updatePixel);
}

void loop() {
  if(digitalRead(INPUT_PIN) == LOW){
    emergency = true;
    digitalWrite(TLK_PIN, HIGH);
    delay(TIME_LEN);
    digitalWrite(TLK_PIN, LOW);
    delay(TIME_LEN);
    digitalWrite(TLK_PIN, HIGH);
    delay(TIME_LEN);
    digitalWrite(TLK_PIN, LOW);
    delay(BREAK_LEN);
  }else{
    emergency = false;
  }
  setEmergency(emergency);
}