#pragma once

#include <stdio.h>
#include <stdlib.h>
//#include "vector.h"
#include "renderer.h"
#include "network.h"
#include "gameObjects.h"

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

void receivedGameSettings();
void receivedUpdate();
