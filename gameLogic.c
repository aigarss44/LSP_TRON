#include "gameLogic.h"

#include <stdio.h>
#include <stdlib.h>

void AddNewPlayer(float x, float y, float angle, Field *field) {
	
	Lightcycle *player = (Lightcycle *) malloc(sizeof(Lightcycle));
	Lightcycle *p;
	//setojam sâkotnçjâs koordinâtas
	player->angle = angle;
	player->x = x;
	player->y = y;
	player->next = NULL;
	player->tailLenght = 0;
	
	//soft gavno
	p = field->player;
	while (p != NULL) {
		p = p->next;
	}
	p->next = player;
	
}

void StartGame () {

	Lightcycle *me;

	Field *field = (Field *) malloc(sizeof(Field));
	field->height = FIELD_HEIGHT;
	field->width = FIELD_WIDTH;

	me = (Lightcycle *) malloc(sizeof(Lightcycle));
	field->player = me;

}

void gameTick() { 
	//printf("tick");		//pabîdîsim visus motociklus uz jaunajâm pozîcijâm
}

