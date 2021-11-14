#include <msp430.h>
#include "switches.h"
#include "led.h"

// To check if a button has been pressed
sw1Down = 0;
sw2Down = 0;
sw3Down = 0;
sw4Down = 0;

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  
  // Update switch interrupt to detect changes from current buttons
  P2IES |= (p2val & SWITCHES);  // If switch up, sense down
  P2IES &= (p2val | ~SWITCHES);   // If switch down, sense up
  
  return p2val;
}

void switch_init()
{
  // Setup switch
  P2REN |= SWITCHES;   // Enables resistors for switches
  P2IE |= SWITCHES;   // Enable interrupts from switches
  P2OUT |= SWITCHES;   // Pull-ups for switches
  P2DIR &= ~SWITCHES;   // Set switches' bits for input
  switch_update_interrupt_sense();
  led_update();
}

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();

  int prev1 = sw1Down;
  int prev2 = sw2Down;
  int prev3 = sw3Down;
  int prev4 = sw4Down;

  // Checks if button has been pressed
  sw1Down = (p2val & SW1) ? 0 : 1;
  sw2Down = (p2val & SW2) ? 0 : 1;
  sw3Down = (p2val & SW3) ? 0 : 1;
  sw4Down = (p2val & SW4) ? 0 : 1;

  // Press button once to turn off, press again to turn off
  if (prev1 != sw1Down && sw1Down){
    oddPress1 ^= 1;
    // One button pressed, all other should be off
    oddPress2 = 0, oddPress3 = 0, oddPress4 = 0;
  }
  else if (prev2 != sw2Down && sw2Down){
    oddPress2 ^= 1;
    oddPress1 = 0, oddPress3 = 0, oddPress4 = 0;
  }
  else if (prev3 != sw3Down && sw3Down){
    oddPress3 ^= 1;
    oddPress1 = 0, oddPress2 = 0, oddPress4 = 0;
  }
  else if (prev4 != sw4Down && sw4Down){
    oddPress4 ^= 1;
    oddPress1 = 0, oddPress2 = 0, oddPress3 = 0;
  }
}
