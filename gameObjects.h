
#ifndef GAME_OBJECTS
#define GAME_OBJECTS

#define MAX_TAIL_LENGTH 100

typedef struct Tail Tail;
struct Tail {
	int tailLenght;
	float tail[MAX_TAIL_LENGTH]; //b�s 2d vektori nevis floati
};

typedef struct Lightcycle Lightcycle;
struct Lightcycle {
	float x;
	float y;
	float angle;	//le��is gr�dos
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
