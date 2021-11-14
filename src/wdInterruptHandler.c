#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

// To keep track of the number of times a button has been pressed
oddPress1 = 0;
oddPress2 = 0;
oddPress3 = 0;
oddPress4 = 0;

void __interrupt_vec(WDT_VECTOR) WDT ()   // 250 interrupts/sec
{
  static int count = 0;

  count++;
  
  if ((count % 63) == 0 && oddPress1 == 1){   // Quarter Notes
    // Play song
    led_update();
    playSong();
    count = 0;
  }
  else if ((count % 31) == 0 && oddPress2 == 1){   // Eighth Notes
    // Play song
    led_update();
    playSong2();
    count = 0;
  }
  else if ((count % 63) == 0 && oddPress3 == 1){  // Quarter Notes
    // Play song
    led_update();
    playSong3();
    count = 0;
  }
  else if ((count % 125) == 0 && oddPress4 == 1){ // Called every 1/2 of a second
    buzzer_set_period(0);
    dim_sequence();
    count = 0;
  }
}
