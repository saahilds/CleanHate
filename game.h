#ifndef GAME_H
#define GAME_H

#include "gba.h"

                    /* TODO: */

            // Create any necessary structs //
typedef struct player {
	int length;
	int width;
	int row;
	int col;
	volatile u16 color;
} Uga, Gatech;
/*
* For example, for a Snake game, one could be:
*
* typedef struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* } Snake;
*
*
*
*
*
* Example of a struct to hold state machine data:
*
* typedef struct state {
*   int currentState;
*   int nextState;
* } State
*
*/

#endif
