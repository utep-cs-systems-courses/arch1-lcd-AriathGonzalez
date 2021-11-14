#include <msp430.h>
#include "led.h"
#include "switches.h"

void led_init()
{
  // P1DIR <- Specifies bits for output
  P1DIR |= LEDS;   // Bits attached to leds are output
  led_update();
}

void led_update()
{
  // P1OUT <- Provides 8 bits of data to output
  // LEDS start off
  P1OUT &= ~LEDS;
}

void redOn(int on)
{
  // 1 for on, 0 for off
  if (on == 0){
    P1OUT &= ~LED_RED;
  }
  else if (on == 1){
    P1OUT |= LED_RED;
  }
}

void greenOn(int on)
{
  // 1 for on, 0 for off
  if (on == 0){
    P1OUT &= ~LED_GREEN;
  }
  else if (on == 1){
    P1OUT |= LED_GREEN;
  }
}

void ledsOn(int on)
{
  // 1 for on, 0 for off
  if (on == 0){
    P1OUT &= ~LEDS;
  }
  else if (on == 1){
    P1OUT |= LEDS;
  }
}

void altLEDS(int on)
{
  // 1 - Red on, Green off
  // 0 - Green on, Red off
  switch(on){
  case 0:
    redOn(1);
    greenOn(0);
    break;
  case 1:
    redOn(0);
    greenOn(1);
    break;
  default:
    ledsOn(0);
    break;
  }
}

