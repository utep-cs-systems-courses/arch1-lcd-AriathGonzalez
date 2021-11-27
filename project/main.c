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

static unsigned char colS = 20;
static unsigned char rowS = 20;
static unsigned char startC = screenHeight / 2;
static unsigned char startR = screenWidth / 2;
// Colors for creeper
static char blue = 7, green = 63, red = 7;
static char blue2 = 0, green2 = 0, red2 = 0;

short redrawScreen = 0;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount++;

  if (secCount >= 63 && oddPress1 == 1){
    buzzer_set_period(0);
    redrawScreen = 1;
    secCount = 0;
  }
  if (secCount >= 63 && oddPress2 == 1){
    buzzer_set_period(0);
    redrawScreen = 1;
    secCount = 0;
  }
  if (secCount >= 63 && oddPress3 == 1){
    buzzer_set_period(0);
    redrawScreen = 1;
    secCount = 0;
  }
  if (secCount >= 63 && oddPress4 == 1){
    redrawScreen = 1;
    playSong();
    secCount = 0;
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
      // Move to the left
      if (oddPress1){
	if (startC == 0)
	  startC = screenHeight / 2;
	else
	  startC -= 5;
	drawCreeper();
      }
      // Move to the right
      else if (oddPress2){
	if (startC + colS == screenHeight)
	  startC = 0;
	else
	  startC += 5;
	drawCreeper();
      }
      // Change base color
      else if (oddPress3){
	green = (green - 1) % 64;
	green2 = (green2 + 1) % 64;
	blue = (blue + 2) % 32;
	blue2 = (blue2 - 2) % 32;
	red = (red + 3) % 32;
	red2 = (red2 - 3) % 32;
	drawCreeper();
      }
      // Change secondary colors
      else if (oddPress4){
	drawString11x16(10, 20, "GAME OVER", COLOR_YELLOW, COLOR_DARK_OLIVE_GREEN);
	drawCreeper();
      }
      redrawScreen = 0;
    }
    greenOn(0);	/* led off */
    or_sr(0x10);	/**< CPU OFF */
    greenOn(1);	/* led on */
  }
}


void drawCreeper ()
{ 
  unsigned int baseC = (blue << 11) | (green << 5) | red;
  unsigned int secondC = (blue2 << 11) | (green2 << 5) | red2;
  
  // Draw Creeper Face
  for (short col = 0; col<= colS; col++){ // 80 max colS
    for (short row = 0; row <= rowS; row++){  // 80 max colR
      drawPixel(startC + col, startR + row, baseC);
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
      drawPixel(startC + col + (colS * .125), startR + row + rowS, baseC);
    }
  }

  // Draw Feet
  for (short col = 0; col <= colS * .75; col++){
    for (short row = 0; row <= rowS * .25; row++){
      drawPixel(startC + col + (colS * .125), startR + row + (rowS * 2), secondC);
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
