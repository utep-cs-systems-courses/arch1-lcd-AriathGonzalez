#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "lcddraw.h"
#include "lcdutils.h"
#include "led.h"
#include "stateMachines.h"
#include "switches.h"

// To keep track of the number of times a button has been pressed
int oddPress1 = 0;
int oddPress2 = 0;
int oddPress3 = 0;
int oddPress4 = 0;

short redrawScreen = 1;

void wdt_c_handler()
{
  static int count = 0;

  count++;

  if ((count % 63) == 0 && oddPress1 == 1){   // Quarter Notes
    // Play song
    redrawScreen = 1;
    count = 0;
  }
  else if ((count % 31) == 0 && oddPress2 == 1){   // Eighth Notes
    // Play song
    redrawScreen = 1;
    count = 0;
  }
  else if ((count % 63) == 0 && oddPress3 == 1){  // Quarter Notes
    // Play song
    redrawScreen = 1;
    count = 0;
  }
  else if ((count % 125) == 0 && oddPress4 == 1){ // Called every 1/2 of a second
    redrawScreen = 1;
    count = 0;
  }
}
int main(void) {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  led_init();
  lcd_init();
  buzzer_init();
  switch_init();
  enableWDTInterrupts();	/* enable periodic interrupt */

  or_sr(0x8);

  clearScreen(COLOR_BLACK);
  while (1){
    if (redrawScreen){
      if (oddPress1){
	playSong();
      }
    }
    or_sr(0x18);   /* CPU off, GIE on */
  }
}
