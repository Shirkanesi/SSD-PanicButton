#define NUMPIXELS   2         //Amount of LED-Pixels (WS2812B)
#define LED_PIN     4         //PIN of WS2812B Data-IN
#define LED_STEP    10        //The step of LED-Fade
#define INIT_BRIGHT 100       //The initial brightnes of every animation

#define INPUT_PIN   2         //PIN with input button (extern)  !important! Button is N.O. and needs to switch to GND
#define TLK_PIN     3         //PIN with Walki Talki  (intern)
#define TIME_LEN    500       //Time between button press (on TLK_PIN) !needs to be adjusted! (miliseconds)
#define BREAK_LEN   10000     //Time between triggers (miliseconds)

#define RUN_LED     5         //Pin of the LED, which shows the scripts activity
#define RUN_LED_LEN 4         //How long the pulse of the RUN_LED is (Seconds)

#define BUZZER_PIN  6         //Pin of the buzzer
#define BUZZ_S_LEN  150       //Lenght of the buzzer-sound (miliseconds)
#define BUZZ_COUNT  3         //Amount of buzzes per trigger
#define BUZZ_FREQ   3         //This value multiplyed with 10 is the time-distance (in Seconds) between buzzer-beeps
#define ACTIVE_BUZZ 0         //Decides, wheather the buzzer is active(1) or passiv(0)

/**
 * PIN-Layout:
 * INPUT_PIN  ->  Input-Buton
 * TLK_PIN    ->  Pin to walki talki
 * LED_PIN    ->  Data-IN-Pin of the LED-Stripe
 * RUN_LED    ->  LED flashing while script runs
 * BUZZER_PIN ->  Buzzer will beep frequently to show the active emergency
 */

 //TODO: Different blink-states --> EEPROM?!?, reset-button?!? ERROR-CODES?
