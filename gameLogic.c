#include "gameLogic.h"

#include <stdio.h>
#include <stdlib.h>

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

	Field *field = (Field *) malloc(sizeof(Field));
	field->height = FIELD_HEIGHT;
	field->width = FIELD_WIDTH;

	me = (Lightcycle *) malloc(sizeof(Lightcycle));
	field->player = me;

	gameField = field;
}

void gameTick() { 
	//printf("tick");		//pab�d�sim visus motociklus uz jaunaj�m poz�cij�m
	RenderField(gameField);
}

void UpdateLightcyclePosition (Lightcycle *player) {
	
	float degreesToTurn = player->targetRotation - player->rotation; // pagaid�m vnk snapo par 90 gr�diem

	player->rotation += degreesToTurn; 
}

void checkCollision () {

}
