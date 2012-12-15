#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#include <stdlib.h>
#endif // !STDIO_H
#include "vector.h"

#define FIELD_WIDTH 160		//lauka pa kuru brauc motocikli izmçri
#define FIELD_HEIGHT 90
#define MAX_TAIL_LENGTH 100

typedef struct Field ;
typedef struct Lightcycle ;

typedef struct {
	float width;
	float height;
	struct Lightcycle *player;
} Field;

typedef struct {
	float x;
	float y;
	float angle;	//leòíis grâdos
	int tailLenght;
	struct Lightcycle *next;
	float tail[MAX_TAIL_LENGTH]; //bûs 2d vektori nevis floati
} Lightcycle;

void gameTick();