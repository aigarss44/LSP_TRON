#pragma once


#include <stdio.h>
#include <stdlib.h>
#include "renderer.h"

#define FIELD_WIDTH 160		//lauka pa kuru brauc motocikli izm�ri
#define FIELD_HEIGHT 90
#define FRAMES_PER_SECOND 5

//cross platform, bitch
#ifdef __unix__ 
# include <unistd.h>
#define WAIT_FOR_NEXT_FRAME usleep(1000000/FRAMES_PER_SECOND);
#elif defined _WIN32 
# include <windows.h>
#define WAIT_FOR_NEXT_FRAME Sleep(1000/FRAMES_PER_SECOND);
#endif

Field *gameField;

void AddNewPlayer(float x, float y, float rotation, Field *field);
void InitGame ();
void gameTick();

void UpdateLightcyclePosition (Lightcycle *player);
void UpdateTail(Lightcycle *player);

void checkCollision (Lightcycle *player);
void checkFieldCollision (Lightcycle *player);
void checkTailCollision (Lightcycle *player);

void updateGameFromServer(int testVar);

/* Otto */
#define MAX_PLAYERS 8
#define MAX_TAIL_SEGS 10

#include "packets.h"
typedef struct _Tail {
	struct UpdateTailHeader uth;
	struct UpdateTail ut[MAX_TAIL_SEGS];
} TailList;
typedef struct _UpdatePackage {

	int player_count;
	struct UpdatePlayer players[MAX_PLAYERS];

	int total_tail_length;
	TailList tails[MAX_PLAYERS];

	int bullet_count;
	struct UpdateBullet *ub;

} UpdatePackage;
void receivedGameSettings(struct ConnectionResponse *cr);
void receivedUpdate(UpdatePackage *up);







