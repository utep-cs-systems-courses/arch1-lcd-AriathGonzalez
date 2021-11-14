#include "led.h"
#include "stateMachines.h"

void dim_sequence()
{
  static int dimState = 0;

  switch (dimState){
  case 0:
    redDim75();
    greenDim25();
    dimState++;
    break;
  case 1:
    redDim25();
    greenDim75();
    dimState++;
    break;
  case 2:
    redDim50();
    greenDim50();
    dimState = 0;
    break;
  default:
    break;
  }
}
