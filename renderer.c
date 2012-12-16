#include "renderer.h"

void Draw(void) {

	glClearColor(0,0,1,1);
	glClear(GL_COLOR_BUFFER_BIT );
	glFlush();
}



void RenderField(Field *field) {
	//sataisi lai vispar kaut ko zime uz ekrana un njem vera aspect ratio (tam laikam kaut k�du init funkciju atsevi��i uztais�si)
	printf("X:%.2f Y:%.2f ROT:%.2f \n", field->player->location.x, field->player->location.y, field->player->rotation);
}
