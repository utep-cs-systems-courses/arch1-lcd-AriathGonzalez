#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h" 
#include "switches.h"

#define LED BIT6		/* note that bit zero req'd for display */

oddPress1 = 0;
oddPress2 = 0;
oddPress3 = 0;
oddPress4 = 0;

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

// axis zero for col, axis 1 for row
short drawPos[2] = {10,10}, controlPos[2] = {10,10};
short velocity[2] = {3,8}, limits[2] = {screenWidth-36, screenHeight-8};

short redrawScreen = 1;
u_int controlFontColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 25) {		/* 10/sec */
    secCount = 0;
    redrawScreen = 1;
  }
}
  
void update_shape();

void main()
{
  
  P1DIR |= LED;		/**< Green led on when CPU on */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLUE);
  
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      update_shape();
    }
    P1OUT &= ~LED;	/* led off */
    or_sr(0x10);	/**< CPU OFF */
    P1OUT |= LED;	/* led on */
  }
}

    
    
void
update_shape()
{
  static unsigned char row = screenHeight / 2, col = screenWidth / 2;   // Middle
  static int colStep = 5, rowStep = 5;
  static char blue = 31, green = 0, red = 31;
  static unsigned char step = 0;
  if (oddPress4) return;
  if (step <= 10) {   // How often the shape is drawn, reach max size
    int startCol = col - step;
    int endCol = col + step;
    int width = 1 + endCol - startCol;
    // a color in this BGR encoding is BBBB BGGG GGGR RRRR
    unsigned int color = (blue << 11) | (green << 5) | red;
    blue++; blue &= 31;
    green += 2; green &= 63;
    
    fillRectangle(startCol, row+step, width, 1, color);
    fillRectangle(startCol, row-step, width, 1, color);
    if (oddPress3) green = (green + 1) % 64;
    if (oddPress2) blue = (blue + 2) % 32;
    if (oddPress1) red = (red - 3) % 32;
    step ++;
  } else {
    col += colStep;   // Moves shape to right
    row += rowStep;   // Moves shape down
    if (col < 20 || col >= (screenWidth - 20)){
      col -= colStep; colStep = -colStep;
    }
    if (row < 20 || row > (screenHeight - 20)){
	row -= rowStep; rowStep = -rowStep;
    }
     clearScreen(COLOR_BLUE);
     step = 0;
  }
}

/* Switch on S2 */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
