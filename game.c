#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "buzz.h" //image
#include "hairy.h" //image
#include "hate.h" //FS image
#include "bobbydodd.h" //FS image
#include "football.h"
//#define REG_DISPCTL *(unsigned short *)0x4000000
/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"

/* TODO: */
// Add any additional states you need for your app.
typedef enum {
  START,
  INSTRUCT,
  INSTRUCT2,
  SETUP,
  GAME,
  WIN,
  LOSE,
} GBAState;

int main(void) {

  
  /* TODO: DONE */ 
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial game state
  GBAState state = START;

  while (1) {
    currentButtons = BUTTONS;  // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw
    int x = 0;
    //waitForVBlank();
    switch (state) {
      case START:
        waitForVBlank();
        drawFullScreenImageDMA(hate);
        drawString(140,25,"Welcome to Hate Week, Jackets!", YELLOW);
        drawString(150,80,"Press ENTER!", YELLOW);
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          state = INSTRUCT;
        }
        break;
      case INSTRUCT:
        waitForVBlank();
        fillScreenDMA(BLACK);
        state = INSTRUCT2;
        if (KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
          state = START;
        }
        break;
      case INSTRUCT2:
        waitForVBlank();
        drawString(10, 0, "You are the Yellow Jacket", WHITE);
        drawString(20, 0, "at the GT vs. UGA game", WHITE);
        drawString(30, 0, "Get to the endzone, don't get tackled", WHITE);
        drawString(40,0,"Use the arrow keys to move", WHITE);
        drawString(50,0,"Press ENTER to begin...", WHITE);
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          state = SETUP;
        }
        if (KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
          state = START;
        }
        break;
      case SETUP:
        waitForVBlank();
        fillScreenDMA(GREEN);
        drawRectDMA(0,220,20,160,WHITE); //endzone

        state = GAME;
        if (KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
          state = START;
        }
        break;
      case GAME:
        
        x = start_running();
        if (x == 1) {
          state = WIN;
          break;
        }
        if (x == 2) {
          state = START;
          break;
        }
        state = LOSE;
        break;
     // state = ?
      case WIN:
        waitForVBlank();
        drawFullScreenImageDMA(bobbydodd);
        drawString(100,90,"GT WINS!",BLACK);
        int time = vBlankCounter/60;

        char a[20];
        drawString(110, 80, "Total time: ", BLACK);
        sprintf(a, "%i", time);
        drawString(110,145,a, BLACK);
        drawString(140,70,"Restart: ENTER", BLACK);
        
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          state = START;
        }
        if (KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
          state = START;
        }

        // state = ?
        break;
      case LOSE:
        waitForVBlank();
        fillScreenDMA(BLACK);
        drawString(60,25,"OH NO GT loses, try again", YELLOW);
        drawString(80,25,"Press ENTER", YELLOW);
        //drawString(140,90, timings, YELLOW);
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          state = START;
        }
        if (KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
          state = START;
        }
        // state = ?
        break;
    }

    previousButtons = currentButtons;  // Store the current state of the buttons
    
  }
  return 0;
}
