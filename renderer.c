#include "renderer.h"

void Draw(void) {

	glClearColor(0,0,1,1);
	glClear(GL_COLOR_BUFFER_BIT );
	glFlush();
}



void RenderField(Field *field) {
	//sataisi lai vispar kaut ko zime uz ekrana un njem vera aspect ratio (tam laikam kaut kâdu init funkciju atseviðíi uztaisîsi)
}
