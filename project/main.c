#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h" 
#include "switches.h"
#include "led.h"
#include "buzzer.h"

oddPress1 = 0;
oddPress2 = 0;
oddPress3 = 0;
oddPress4 = 0;

// axis zero for col, axis 1 for row
short drawPos[2] = {10,10}, controlPos[2] = {10,10};
short velocity[2] = {3,8}, limits[2] = {screenWidth-36, screenHeight-8};

short redrawScreen = 1;
u_int controlFontColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 63) {
    //playSong();
    secCount = 0;
    redrawScreen = 1;
  }
}

void drawCreeper();
//void update_shape();

void main()
{
  
  greenOn(1);
  configureClocks();
  lcd_init();
  led_init();
  buzzer_init();
  switch_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLUE);
  
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      drawCreeper();
      // update_shape();
    }
    greenOn(0);	/* led off */
    or_sr(0x10);	/**< CPU OFF */
    greenOn(1);	/* led on */
  }
}


void drawCreeper ()
{
  static unsigned char colS = 20;
  static unsigned char rowS = 20;
  static unsigned char startC = screenHeight / 2;
  static unsigned char startR = screenWidth / 2;

  if (oddPress1){
    if (startC == 0)
      startC = screenHeight / 2;
    else
      startC -= 5;
  }
  if (oddPress2){
    if (startC + colS == screenHeight)
      startC = 0;
    else
      startC += 5;
  }
  
  // Draw Creeper Face
  for (short col = 0; col<= colS; col++){ // 80 max colS
    for (short row = 0; row <= rowS; row++){  // 80 max colR
      drawPixel(startC + col, startR + row, COLOR_GREEN);
    }
  }

  // Eyes
  for (short col = 0; col <= colS * .25; col++){  // 20  1/4 of colS
    for (short row = 0; row <= rowS * .25; row++){  // 20  1/4 of rowS
      drawPixel(startC + col + (colS * .125), startR + row + (rowS * .125), COLOR_BLACK);  // col + 1/8 of colS and row + 1/8 rowS
    }
  }

  for (short col = 0; col <= colS * .25; col++){
    for (short row = 0; row <= rowS * .25; row++){
      drawPixel(startC + col + (colS * .625), startR + row + (rowS * .125), COLOR_BLACK);  // col + 5/8 of colS and row + 1/10 rowS
    }
  }

  // Base mouth
  for (short col = 0; col <= colS * .25; col++){  // 1/4 of colS
    for (short row = 0; row <= rowS * .375; row++){ // 3/8 of rowS
      drawPixel(startC + col + (colS * .375),startR + row + (rowS * .375), COLOR_BLACK);
    }
  }

  // Side mouth
  for (short col = 0; col <= colS * .125; col++){
    for (short row = 0; row <= rowS * .375; row++){
      drawPixel(startC + col + (colS * .25), startR + row + (rowS * .5), COLOR_BLACK);
    }
  }

  for (short col = 0; col <= colS * .125; col++){
    for (short row = 0; row <= rowS * .375; row++){
      drawPixel(startC + col + (colS * .625),startR + row + (rowS * .5), COLOR_BLACK);
    }
  }

  // Draw Body
  for (short col = 0; col <= colS * .75; col++){
    for (short row = 0; row <= rowS; row++){
      drawPixel(startC + col + (colS * .125), startR + row + rowS, COLOR_GREEN);
    }
  }

  // Draw Feet
  for (short col = 0; col <= colS * .75; col++){
    for (short row = 0; row <= rowS * .25; row++){
      drawPixel(startC + col + (colS * .125), startR + row + (rowS * 2), COLOR_WHITE);
    }
  }

  for (short col = 0; col <= colS * .75; col++) {
    for (short row = 0; row <= rowS *.25; row++){
      drawPixel(startC + col + (colS * .125), startR + row + (rowS * 2.25), COLOR_BLACK);
    }
  }
  clearScreen(COLOR_BLUE);
}
/*
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
*/
