#include "gameLogic.h"

#include <stdio.h>
#include <stdlib.h>

void AddNewPlayer(float x, float y, float rotation, Field *field) {
	
	Lightcycle *player = (Lightcycle *) malloc(sizeof(Lightcycle));
	Lightcycle *p;

	//setojam sâkotnçjâs koordinâtas
	player->rotation = rotation;
	player->location.x = x;
	player->location.y = y;
	player->next = NULL;
	player->tail->tailLenght = 0;
	
	//pievienojam spçlçtâju laukumam
	p = field->player;
	while (p != NULL) {
		p = p->next;
	}
	p->next = player;
	
}

void InitGame () {

	Lightcycle *me;

	Field *field = (Field *) malloc(sizeof(Field));
	field->height = FIELD_HEIGHT;
	field->width = FIELD_WIDTH;

	me = (Lightcycle *) malloc(sizeof(Lightcycle));
	field->player = me;

	gameField = field;
}

void gameTick() { 
	//printf("tick");		//pabîdîsim visus motociklus uz jaunajâm pozîcijâm
	RenderField(gameField);
}

void UpdateLightcyclePosition (Lightcycle *player) {
	
	float degreesToTurn = player->targetRotation - player->rotation; // pagaidâm vnk snapo par 90 grâdiem

	player->rotation += degreesToTurn; 
}

void checkCollision () {

}
