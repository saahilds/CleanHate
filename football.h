#ifndef FOOTBALL_H
#define FOOTBALL_H

#include "gba.h"
#include <string.h>

typedef struct
{
	int r;
	int c;
	int w;
	int h;
} RETURNER;

typedef struct 
{
	int r;
	int c;
	int dr;
	int w;
	int h;
} DEFENDER;

int start_running(void);

int tackle_collision(int RETURNER_r, int RETURNER_c, int RETURNER_w, int RETURNER_h, int DEFENDER_r, int DEFENDER_c, int DEFENDER_w, int DEFENDER_h);

#endif