#include "football.h"
#include "gba.h"
#include "game.h"
#include "buzz.h"
#include "hairy.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int start_running(void) {
	DEFENDER hairy_1 = {0,0,0,0,0};
	hairy_1.r = 0;
	hairy_1.c = randint(40,189);
	hairy_1.dr = 2;
	hairy_1.w = HAIRY_WIDTH;
	hairy_1.h = HAIRY_HEIGHT;


	while (1) {
		RETURNER buzz_1 = {0,0,0,0};
		buzz_1.r = 80;
		buzz_1.w = BUZZ_WIDTH;
		buzz_1.h = BUZZ_HEIGHT;

		drawString(0, 0, "Down: 4", BLACK);
		int time = 0;
		//char t[2];
		//itoa(time, t, 10);

		// char all[10];
		// all[0] = 'T';
		// all[1] = 'i';
		// all[2] = 'm';
		// all[3] = 'e';
		// all[4] = ':';
		// all[5] = ' ';
		// all[6] = time;
		

		//drawString(10,0, all, BLACK);
		drawImageDMA(buzz_1.r, buzz_1.c, buzz_1.w, buzz_1.h, buzz);

		while (1) {
			
			hairy_1.r += hairy_1.dr;
			if (hairy_1.r < 2) {
				hairy_1.r = 2;
				hairy_1.dr *= -1;

			}
			if (hairy_1.r > 138) {
				hairy_1.r = 138;
				hairy_1.dr *= -1;
			}
			waitForVBlank();

			drawRectDMA(0,hairy_1.c,HAIRY_WIDTH, 160, GREEN); //fill entire column where Hairy used to be

			drawImageDMA(hairy_1.r, hairy_1.c, HAIRY_WIDTH, HAIRY_HEIGHT, hairy);


			int gg = 0;
			

			if (KEY_DOWN(BUTTON_UP, BUTTONS)) {
				buzz_1.r--;
				if (buzz_1.r < 10) {
					buzz_1.r = 10;
				}
				else {
					drawRectDMA(buzz_1.r + BUZZ_HEIGHT, buzz_1.c, BUZZ_WIDTH, 1, GREEN);
				}
				
				
			}

			if (KEY_DOWN(BUTTON_DOWN, BUTTONS)) {
				buzz_1.r++;
				if (buzz_1.r > 138) {
					buzz_1.r = 138;
				}
				else {
					drawRectDMA(buzz_1.r - 1, buzz_1.c, BUZZ_WIDTH, 1, GREEN);
				}
				
			}

			if (KEY_DOWN(BUTTON_RIGHT, BUTTONS)) {
				buzz_1.c++;
				if (buzz_1.c > 219) {
					buzz_1.c = 220;
				}
				else {
					drawRectDMA(buzz_1.r, buzz_1.c - 1, 1, BUZZ_HEIGHT, GREEN);
				}
				
			}

			if (KEY_DOWN(BUTTON_LEFT, BUTTONS)) {
				buzz_1.c--;
				if (buzz_1.c < 0) {
					buzz_1.c = 0;
				}
				else {
					drawRectDMA(buzz_1.r, buzz_1.c + BUZZ_WIDTH, 1, BUZZ_HEIGHT, GREEN);
				}
			}
			
			if (buzz_1.c + BUZZ_WIDTH > 219) {
				gg = 1;
				time = 0;
				return gg;
			}
			if (tackle_collision(buzz_1.r, buzz_1.c, BUZZ_WIDTH, BUZZ_HEIGHT,hairy_1.r, hairy_1.c, HAIRY_WIDTH, HAIRY_HEIGHT) == 1) {
				gg = 0;
				time = 0;
				return gg;
			}
			if (KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
				time = 0;
				return 2;
			}
			if (gg < 1) {
				time = vBlankCounter/60;
				char str[20];
				drawString(10,0, "Time: ", BLACK);
				sprintf(str, "%i", time);
				drawRectDMA(10,40,20,10,GREEN);
				drawString(10,40,str, BLACK);
				drawImageDMA(buzz_1.r, buzz_1.c, BUZZ_WIDTH, BUZZ_HEIGHT, buzz);
			}
			
		}

	}
	return 0;
}

int tackle_collision(int RETURNER_r, int RETURNER_c, int RETURNER_w, int RETURNER_h, int DEFENDER_r, int DEFENDER_c, int DEFENDER_w, int DEFENDER_h) {
	if (((((RETURNER_r + RETURNER_h) > DEFENDER_r) && (RETURNER_r < DEFENDER_r)) || (((DEFENDER_r + DEFENDER_h) > RETURNER_r) && (DEFENDER_r < RETURNER_r)))
		&& (((((RETURNER_c + RETURNER_w) > DEFENDER_c) && (RETURNER_c < DEFENDER_c)) || (((DEFENDER_c + DEFENDER_w) > RETURNER_c) && (DEFENDER_c < RETURNER_c))))) {
		return 1;
	}
	return 0;
}