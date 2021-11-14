/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  // Not part of original code
  short centerR = LONG_EDGE_PIXELS / 2;   // Center coord for the rows
  short centerC = SHORT_EDGE_PIXELS / 2;  // Center coord for the cols
  
  short col = 0, row = 0;
  short startc = SHORT_EDGE_PIXELS / 2, startr = LONG_EDGE_PIXELS / 2;

  /*
  // Creates a Diamond
  for (int c = 30; c >= 0; c--) {
    for (int j = 0; j <= c; j++){
      short r = 30 -c;   // Determine length of row
      drawPixel (centerC + j, centerR + r, COLOR_WHITE);
      drawPixel (centerC + j, centerR - r, COLOR_PINK);
      drawPixel (centerC -j, centerR + r, COLOR_RED);
      drawPixel (centerC - j, centerR - r, COLOR_YELLOW);
    }
  }
  */

  // Creates Hourglass
  /*
  for (col = 0; col < 30; col++){
    row = col;
    short leftEdge = -col;
    short rightEdge = col;
    
    for (short c = leftEdge; c <= rightEdge; c++){
      drawPixel (startc + c, startr + row, COLOR_PINK);
      drawPixel (startc + c, startr - row, COLOR_RED);
    }
  }
  */

  // Draw y
  /*
  for (col = 0; col <= 30; col++){
    row = col;
    drawPixel (centerC + col, centerR - row, COLOR_BLACK);
  }

  for (col = 0; col <= 15; col++){
    row = col;
    drawPixel ((centerC - col) + 15, (centerR - row) - 15, COLOR_BLACK);
  }
  */

  /*
  // Draw Creeper Face
  for (int col = 0; col<= 80; col++){
    for (int row = 0; row <= 80; row++){
      drawPixel(col, row, COLOR_GREEN);
    }
  }
  
  // Eyes
  for (int col = 0; col <= 20; col++){
    for (int row = 0; row <= 20; row++){
      drawPixel(col + 10, row + 10, COLOR_BLACK);
    }
  }
  
   for (int col = 0; col <= 20; col++){
    for (int row = 0; row <= 20; row++){
      drawPixel(col + 50, row + 10, COLOR_BLACK);
    }
  }
  
  // Base mouth
  for (int col = 0; col <= 20; col++){
    for (int row = 0; row <= 30; row++){
      drawPixel(col + 30, row + 30, COLOR_BLACK);
    }
  }
  
  // Side mouth
  for (int col = 0; col <= 10; col++){
    for (int row = 0; row <= 30; row++){
      drawPixel(col + 20, row + 40, COLOR_BLACK);
    }
  }
  
  for (int col = 0; col <= 10; col++){
    for (int row = 0; row <= 30; row++){
      drawPixel(col + 50, row + 40, COLOR_BLACK);
    }
  }
  */
  
  // Original code
    /*
  drawString5x7(20,20, "hello", COLOR_BLACK_GREEN, COLOR_BLACK_RED);

  fillRectangle(30,30, 60, 60, COLOR_BLACK_ORANGE);*/

  
  short c = 40;
  short r = 40;
  drawCreeper(centerC, centerR, c, r);

}

void drawCreeper (short startC, short startR, short colS, short rowS){
  
  // Draw Creeper Face
  for (short col = 0; col<= colS; col++){ // 80 max colS
    for (short row = 0; row <= rowS; row++){  // 80 max colR
      drawPixel(startC + col, startR + row, COLOR_GREEN);
    }
  }
  
  // Eyes
  for (short col = 0; col <= colS * .25; col++){  // 20  1/4 of colS
    float c = colS * .125;
    float r = rowS * .125;
    for (short row = 0; row <= rowS * .25; row++){  // 20  1/4 of rowS
      drawPixel(startC + col + c, startR + row + r, COLOR_BLACK);  // col + 1/8 of colS and row + 1/8 rowS
    }
  }
   
   for (int col = 0; col <= colS * .25; col++){
    for (int row = 0; row <= rowS * .25; row++){
      drawPixel(startC + col + (colS * .625), startR + row + (rowS * .125), COLOR_BLACK);  // col + 5/8 of colS and row + 1/10 rowS
    }
  }

   
  // Base mouth
   for (int col = 0; col <= colS * .25; col++){  // 1/4 of colS
     for (int row = 0; row <= rowS * .375; row++){ // 3/8 of rowS
       drawPixel(startC + col + (colS * .375),startR + row + (rowS * .375), COLOR_BLACK);
    }
  }
  
  // Side mouth
   for (int col = 0; col <= colS * .125; col++){
    for (int row = 0; row <= rowS * .375; row++){
      drawPixel(startC + col + (colS * .25), startR + row + (rowS * .5), COLOR_BLACK);
    }
  }
  
  for (int col = 0; col <= colS * .125; col++){
    for (int row = 0; row <= rowS * .375; row++){
      drawPixel(startC + col + (colS * .625),startR + row + (rowS * .5), COLOR_BLACK);
    }
  }
}
