#include "toolbox.h"

void ground_plane(float w, float h) {

	float x = w;
	float z = h;
	float y = 0;

	float hx = x/2.0f;
	float hz = z/2.0f;

	glColor3f(0.8f, 0.1f, 0.0f);
	glBegin(GL_LINES);
	int i;
	for (i = 0; i <= h; i++) {
		glVertex3f(-hx, y, -hz + i);
		glVertex3f(hx, y, -hz + i);
	}
	for (i = 0; i <= w; i++) {
		glVertex3f(-hx + i, y, -hz);
		glVertex3f(-hx + i, y, hz);
	}
	glEnd();

	/*
	glColor3f(0.8f, 0.1f, 0.0f);
	glBegin(GL_LINE_LOOP);
		glVertex3f(-x, y, -z);
		glVertex3f(x, y, -z);
		glVertex3f(x, y, z);
		glVertex3f(-x, y, z);
	glEnd();
	*/


}
void render_axes() {

	float k = 500.0f;

	glBegin(GL_LINES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-k, 0, 0);
		glVertex3f(k, 0, 0);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0, -k, 0);
		glVertex3f(0, k, 0);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0, 0, -k);
		glVertex3f(0, 0, k);

	glEnd();
}
