#include "gameLogic.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "serveris/packets.h"

void receivedGameSettings(struct ConnectionResponse *settings) {

}
void receivedUpdate() {

}


void AddNewPlayer(float x, float y, float rotation, Field *field) {
	
	Lightcycle *player = (Lightcycle *) malloc(sizeof(Lightcycle));
	Lightcycle *p;

	//setojam s�kotn�j�s koordin�tas
	player->rotation = rotation;
	player->location.x = x;
	player->location.y = y;
	player->next = NULL;
	player->tail->tailLenght = 0;
	
	//pievienojam sp�l�t�ju laukumam
	p = field->player;
	while (p != NULL) {
		p = p->next;
	}
	p->next = player;
	
}

void InitGame () {

	Lightcycle *me;
	Tail *myTail;

	Field *field = (Field *) malloc(sizeof(Field));
	field->height = FIELD_HEIGHT;
	field->width = FIELD_WIDTH;

	myTail = (Tail *) malloc(sizeof(Tail));
	me = (Lightcycle *) malloc(sizeof(Lightcycle));
	me->rotation = 90;
	me->targetRotation = 90;
	me->previousSolidRotation = 90;

	me->location.x = 0;
	me->location.y = 0;
	me->targetLocation.x = 0;
	me->targetLocation.y = 0;
	me->previousSolidLocation.x = 0;
	me->previousSolidLocation.y = 0;

	me->next = NULL;
	me->tail = myTail;
	me->tail->tailLenght = 0;

	field->player = me;

	gameField = field;
}

void updateGameFromServer(int testVar) {
	printf("updateGameFromServer: %i", testVar);
}

void gameTick(void) { 
	//printf("tick \n");		//pab�d�sim visus motociklus uz jaunaj�m poz�cij�m
	//Sleep(1000/FRAMES_PER_SECOND);			//TODO linux analogu. �obr�d tiek izmantota <windows.h> versija
	WAIT_FOR_NEXT_FRAME
	UpdateLightcyclePosition(gameField->player);
	checkCollision(gameField->player);
	RenderField(gameField);
}

void UpdateLightcyclePosition (Lightcycle *player) {
	
	player->rotation = player->targetRotation;

	if (player->rotation < 0)
	{
		player->rotation += 360.0f;
	}
	if (player->targetRotation < 0)
	{
		player->targetRotation += 360.0f;
	}
	if (player->previousSolidRotation < 0)
	{
		player->previousSolidRotation += 360.0f;
	}

	player->rotation = fmod(player->rotation, 360.0f);
	player->targetRotation = fmod(player->targetRotation, 360.0f);
	player->previousSolidRotation = fmod(player->previousSolidRotation, 360.0f);


	if (fabs(player->targetRotation) < 0.01f) {
		player->targetLocation.x += 1.0f;
	} else if ((fabs(player->targetRotation) < 90.01f) && (fabs(player->targetRotation) > 89.99f)) {
		player->targetLocation.y += 1.0f;
	} else if ((fabs(player->targetRotation) < 180.01f) && (fabs(player->targetRotation) > 179.99f)) {
		player->targetLocation.x -= 1.0f;
	} else if ((fabs(player->targetRotation) < 270.01f) && (fabs(player->targetRotation) > 269.99f)) {
		player->targetLocation.y -= 1.0f;
	} else {
		printf("ERROR. rotation problems\n");
	}

	player->location.x = player->targetLocation.x;
	player->location.y = player->targetLocation.y;

}

void UpdateTail(Lightcycle *player) {

}

void checkCollision (Lightcycle *player) {

	checkFieldCollision(player);
	checkTailCollision(player);
}

void checkFieldCollision (Lightcycle *player) {

	//printf("X: %.2f Y: %.2f rot: %.2f\n", player->location.x, player->location.y, player->rotation);

	if ((player->targetLocation.x > FIELD_WIDTH) || (player->targetLocation.y > FIELD_HEIGHT) || (player->targetLocation.x < 0) || (player->targetLocation.y < 0))
	{
		printf("player colision with level bounds");
	}
}

void checkTailCollision (Lightcycle *player) {
	
}
