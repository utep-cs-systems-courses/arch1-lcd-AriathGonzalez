#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "notes.h"

static int toggleRed = 0;
static int toggleGreen = 0;

// Red will be on for 1/4 of time, causing a dimness of 25%
void redDim25()
{
  switch (toggleRed){
  case 0:
    redOn(0);
    toggleRed++;
  case 1:
    toggleRed++;
  case 2:
    toggleRed++;
    break;
  case 3:
    redOn(1);
    toggleRed = 0;
    break;
  default:
    break;
  }
}

// Red will be on for 1/2 of time, causing a dimness of 50%
void redDim50()
{
  switch (toggleRed){
  case 0:
    redOn(1);
    toggleRed++;
    break;
  case 1:
    redOn(0);
    toggleRed++;
    break;
  case 2:
    toggleRed++;
    break;
  case 3:
    redOn(1);
    toggleRed = 0;
  default:
    break;
  }
}

// Red will be on for 3/4 of time, causing a dimness of 75%
void redDim75()
{
  switch(toggleRed){
  case 0:
    redOn(0);
    toggleRed++;
    break;
  case 1:
    toggleRed++;
    break;
  case 2:
    toggleRed++;
    break;
  case 3:
    redOn(1);
    toggleRed = 0;
    break;
  default:
    break;
  }
}

// Green will be on for 1/4 of time, causing a dimness of 25%
void greenDim25()
{
  switch (toggleGreen){
  case 0:
    greenOn(0);
    toggleGreen++;
  case 1:
    toggleGreen++;
  case 2:
    toggleGreen++;
    break;
  case 3:
    greenOn(1);
    toggleGreen = 0;
    break;
  default:
    break;
  }
}

// Green will be on for 1/2 of time, causing a dimness of 50%
void greenDim50()
{
  switch (toggleGreen){
  case 0:
    greenOn(1);
    toggleGreen++;
    break;
  case 1:
    greenOn(0);
    toggleGreen++;
    break;
  case 2:
    toggleGreen++;
    break;
  case 3:
    greenOn(1);
    toggleGreen = 0;
  default:
    break;
  }
}

// Green will be on for 3/4 of time, causing a dimness of 75%
void greenDim75()
{
  switch(toggleGreen){
  case 0:
    greenOn(0);
    toggleGreen++;
    break;
  case 1:
    toggleGreen++;
    break;
  case 2:
    toggleGreen++;
    break;
  case 3:
    greenOn(1);
    toggleGreen = 0;
    break;
  default:
    break;
  }
}

// Play Overlord OP
void playSong()
{
  static char currNote = 0;  // Keep track of state
  // All notes of song
  int notes[15] = {GSHARP, GSHARP, 0, B, B, 0, ASHARP, ASHARP, ASHARP, A, 0, E, 0, DSHARP, 0};
  int n = 15;

  // To go through array of notes
  if (currNote < n){
    buzzer_set_period(notes[currNote]);
    currNote++;
  }
  // Reached end of song, therefore, time to reset
  else{
    currNote = 0;
  }
}

// Play Gerudo Valley while alternating LEDs
void playSong2()
{
  static char currNote = 0;
  
  
  switch(currNote){
    case 0:
      buzzer_set_period(CSHARP);
      altLEDS(1);
      currNote++;
      break;
    case 1:
      buzzer_set_period(FSHARP);
      altLEDS(0);
      currNote++;
      break;
    case 2:
      buzzer_set_period(GSHARP);
      altLEDS(1);
      currNote++;
      break;
    case 3:
      buzzer_set_period(A);
      altLEDS(0);
      currNote++;
      break;
    case 5:  // Note will hold on for 2 periods
      buzzer_set_period(CSHARP);
      altLEDS(1);
      currNote++;
      break;
    case 7:
      buzzer_set_period(FSHARP);
      altLEDS(0);
      currNote++;
      break;
    case 8:  // Note will hold on for 2 periods
      buzzer_set_period(GSHARP);
      altLEDS(1);
      currNote++;
      break;
    case 10:  // Note will hold on for 4 periods
      buzzer_set_period(A);
      altLEDS(0);
      currNote++;
      break;
    case 14:
      buzzer_set_period(D);
      altLEDS(1);
      currNote++;
      break;
    case 15:
      buzzer_set_period(FSHARP);
      altLEDS(0);
      currNote++;
      break;
    case 16:  // Note will hold on for 2 periods
      buzzer_set_period(GSHARP);
      altLEDS(1);
      currNote++;
      break;
    case 18:
      buzzer_set_period(D);
      altLEDS(0);
      currNote++;
      break;
    case 20:
      buzzer_set_period(FSHARP);
      altLEDS(1);
      currNote++;
      break;
    case 21:
      buzzer_set_period(GSHARP);
      altLEDS(0);
      currNote++;
      break;
    case 22:
      buzzer_set_period(A);
      altLEDS(1);
      currNote++;
      break;
    case 26:  // Reached end of song, time to reset to beginning
      buzzer_set_period(0);
      ledsOn(0);
      currNote = 0;
      break;
    default:
      currNote++;
      break;
   }
}

// Play Green Hill Zone
void playSong3()
{
  static char currNote = 0;
  // All notes of song, 0s are for break in between notes
  int notes[28] = {C, A, C, 0, B, 0, C, B, 0, G, G, G, 0, A, E, D, 0, C, 0, B, 0, C, B, 0, G, G, G,                   0};
  int n = 28;

  if (currNote < n){
      buzzer_set_period(notes[currNote]);
      currNote++;
  }
  else {
    currNote = 0;
  }
  
}
