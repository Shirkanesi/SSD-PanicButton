#define NUMPIXELS   2         //Amount of LED-Pixels (WS2812B)
#define LED_PIN     4         //PIN of WS2812B Data-IN
#define LED_STEP    10        //The step of LED-Fade

#define INPUT_PIN   2         //PIN with input button (extern)  !important! Button is NO and needs to switch to GND
#define TLK_PIN     3         //PIN with Walki Talki  (intern)
#define TIME_LEN    500       //Time between button press (on TLK_PIN) !needs to be adjusted!
#define BREAK_LEN   10000     //Time between triggers

#define RUN_LED     5         //Pin of the LED, which shows the scripts activity
#define RUN_LED_LEN 1         //How long the pulse of the RUN_LED is (Seconds)

/**
 * PIN-Layout:
 * INPUT_PIN  ->  Input-Buton
 * TLK_PIN    ->  Pin to walki talki
 * LED_PIN    ->  Data-IN-Pin of the LED-Stripe
 */
