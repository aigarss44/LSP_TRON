#include "gameLogic.h";


void AddNewPlayer(float x, float y, float angle, Field *field) {
	Lightcycle *player = (Lightcycle *) malloc(sizeof(Lightcycle));
	//setojam s�kotn�j�s koordin�tas
	player->angle = angle;
	player->x = x;
	player->y = y;
	player->next = NULL;
	player->tailLenght = 0;

	//soft gavno
	Lightcycle *p = field->player;
	while (p != NULL) {
		p = p->next;
	}
	p->next = player;
}

void StartGame () {
	Field *field = (Field *) malloc(sizeof(Field));
	field->height = FIELD_HEIGHT;
	field->width - FIELD_HEIGHT;
	Lightcycle *me = (Lightcycle *) malloc(sizeof(Lightcycle));
	//field->player = me; kas vi�am nepat�k?

}

void gameTick() { 
	//printf("tick");		//pab�d�sim visus motociklus uz jaunaj�m poz�cij�m
}

