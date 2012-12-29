#include "renderer.h"
#include "vector.h"
#include "toolbox.h"

void Draw(void) {

}

void init_renderer() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.3f, 0.3f, 0.4f, 1.0f);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = WINDOW_WIDTH/(float)WINDOW_HEIGHT;
	gluPerspective(60, aspect, 0.01f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(	0, 90, 0,
				0, 0, 0,
				0, 0, 1);

}


void render_player(Lightcycle *player);
void render_tail(Tail *tail);

float field_w = 2.0f;
float field_h = 2.0f;

void RenderField(Field *field) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Lightcycle *players = field->player;

	field_w = field->width;
	field_h = field->height;

	ground_plane(field_w, field_h);
	render_axes();

	while (players != 0) {
		render_player(players);
		players = players->next;
	}

	glFlush();
}

void render_player(Lightcycle *player) {

	Tail *tail = player->tail;

	float x = player->location.x;
	float y = player->location.y;
	render_quad(x, y);
	printf("%f %f\n", x, y);

	if (tail != 0)
		render_tail(tail);
}
void render_tail(Tail *tail) {

	int len = tail->tailLenght;
	int i;
	for (i = 0; i < len; i++) {

	}
}










