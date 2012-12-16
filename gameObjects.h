
#ifndef GAME_OBJECTS
#define GAME_OBJECTS

#define MAX_TAIL_LENGTH 100

#include "vector.h"

typedef struct Tail Tail;
struct Tail {
	int tailLenght;
	float tail[MAX_TAIL_LENGTH]; //b�s 2d vektori nevis floati
};

typedef struct Lightcycle Lightcycle;
struct Lightcycle {
	vec2 location;			//kur vi�u renderot uz ekr�na
	vec2 targetLocation;	//tiek izmantots anim�cijai
	float rotation;			//le��is gr�dos. �o izmanto pie rendero�anas
	float targetRotation;	//le��is, k�du m��inam sasniegt. tiek izmantots lai pagriezienos b�tu vis maz kaut k�da anim�cija
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
