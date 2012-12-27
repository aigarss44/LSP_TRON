#pragma once

#ifndef GAME_OBJECTS
#define GAME_OBJECTS

#define MAX_TAIL_LENGTH 100
#define ROTATION_FRAME_COUNT 10
#define TRANSLATION_FRAME_COUNT 5

#include "vector.h"

typedef struct Tail Tail;
struct Tail {
	int tailLenght;
	float tail[MAX_TAIL_LENGTH]; //bûs 2d vektori nevis floati
};

typedef struct Lightcycle Lightcycle;
struct Lightcycle {
	
	//pieòemam ka +x ir pa labi un +y ir uz augðu
	vec2 location;			//kur viòu renderot uz ekrâna
	vec2 targetLocation;	//tiek izmantots animâcijai
	vec2 previousSolidLocation;

	//pieòemam ka 0 grâdi ir ekrânam pa labi un 90 ir uz augðu
	float rotation;			//leòíis grâdos. ðo izmanto pie renderoðanas. 
	float targetRotation;	//leòíis, kâdu mçìinam sasniegt. tiek izmantots lai pagriezienos bûtu vis maz kaut kâda animâcija
	float previousSolidRotation;
	Lightcycle *next;
	Tail *tail;
};

typedef struct Field Field;
struct Field {
	float width;
	float height;
	Lightcycle *player;
};

#endif // !GAME_OBJECTS
