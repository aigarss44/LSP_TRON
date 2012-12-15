#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#include <stdlib.h>
#endif // !STDIO_H
#include "vector.h"

#define FIELD_WIDTH 160		//lauka pa kuru brauc motocikli izm�ri
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
	float angle;	//le��is gr�dos
	int tailLenght;
	struct Lightcycle *next;
	float tail[MAX_TAIL_LENGTH]; //b�s 2d vektori nevis floati
} Lightcycle;

void gameTick();