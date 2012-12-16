#include <stdio.h>
#include <stdlib.h>
//#include "vector.h"
#include "renderer.h"
#include "gameObjects.h"

#define FIELD_WIDTH 160		//lauka pa kuru brauc motocikli izmçri
#define FIELD_HEIGHT 90

Field *gameField;

void AddNewPlayer(float x, float y, float rotation, Field *field);
void InitGame ();
void gameTick();