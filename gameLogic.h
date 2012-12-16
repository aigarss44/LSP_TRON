#include <stdio.h>
#include <stdlib.h>
//#include "vector.h"

#define FIELD_WIDTH 160		//lauka pa kuru brauc motocikli izmçri
#define FIELD_HEIGHT 90
#define MAX_TAIL_LENGTH 100


typedef struct Lightcycle Lightcycle;
struct Lightcycle {
	float x;
	float y;
	float angle;	//leòíis grâdos
	int tailLenght;
	Lightcycle *next;
	float tail[MAX_TAIL_LENGTH]; //bûs 2d vektori nevis floati
};

typedef struct Field Field;
struct Field {
	float width;
	float height;
	Lightcycle *player;
};



void gameTick();