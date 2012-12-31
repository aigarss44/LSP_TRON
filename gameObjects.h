#pragma once

#define MAX_TAIL_LENGTH 100
#define ROTATION_FRAME_COUNT 10
#define TRANSLATION_FRAME_COUNT 5

#include "vector.h"

typedef struct Tail Tail;
struct Tail {
	int tailLenght;
	vec2 tail[MAX_TAIL_LENGTH]; //b�s 2d vektori nevis floati
};

typedef struct Lightcycle Lightcycle;
struct Lightcycle {
	
	//pie�emam ka +x ir pa labi un +y ir uz aug�u
	vec2 location;			//kur vi�u renderot uz ekr�na
	vec2 targetLocation;	//tiek izmantots anim�cijai
	vec2 previousSolidLocation;

	//pie�emam ka 0 gr�di ir ekr�nam pa labi un 90 ir uz aug�u
	float rotation;			//le��is gr�dos. �o izmanto pie rendero�anas. 
	float targetRotation;	//le��is, k�du m��inam sasniegt. tiek izmantots lai pagriezienos b�tu vis maz kaut k�da anim�cija
	float previousSolidRotation;
	Lightcycle *next;
	Tail *tail;
};

typedef struct Field Field;
struct Field {
	int playerCount;
	float width;
	float height;
	Lightcycle *player;
};

