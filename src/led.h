#ifndef led_included
#define led_included

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)        // P1.0 | P1.6

void led_init();
void led_update();
void redOn(int on);
void greenOn(int on);
void ledsOn(int on);
void altLEDS(int on);

#endif // included
