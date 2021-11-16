#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "buzzer.h"
#include "notes.h"
#include "stateMachines.h"
#include "switches.h"

short redrawScreen = 1;

int main ()
{
  greenOn(1);
  configureClocks();
  switch_init();
  buzzer_init();
  led_init();
  lcd_init();
  enableWDTInterrupts();  // Enable period interrupt

  or_sr(0x8);   // GIE (enable interrupts)

  clearScreen(COLOR_BLUE);

  short centerR = LONG_EDGE_PIXELS / 2;   // Center coord for the rows
  short centerC = SHORT_EDGE_PIXELS / 2;  // Center coord for the cols
  
  for (int c = 30; c >= 0; c--) {
    for (int j = 0; j <= c; j++){
      short r = 30 -c;   // Determine length of row
      drawPixel (centerC + j, centerR + r, COLOR_WHITE);
      drawPixel (centerC + j, centerR - r, COLOR_PINK);
      drawPixel (centerC -j, centerR + r, COLOR_RED);
      drawPixel (centerC - j, centerR - r, COLOR_YELLOW);
    }
  }
  /*while (1){
    if (redrawScreen){
      redrawScreen = 0;
      //if (oddPress1 == 1){
      //playSong();
      //}
    }
    greenOn(0);
    or_sr(0x10);
    }*/
}


void wtd_c_handler()
{
  static int interruptCount = 0;

  interruptCount++;
  
  if ((interruptCount % 250) == 0){
    redrawScreen = 1;
    interruptCount = 0;
  }
}
