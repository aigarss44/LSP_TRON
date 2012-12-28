#include "toolbox.h"

void ground_plane(float w, float h) {

	float x = x;
	float z = h;
	float y = 0;

	glColor3f(0.8f, 0.1f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(-x, y, -z);
		glVertex3f(x, y, -z);
		glVertex3f(x, y, z);
		glVertex3f(-x, y, z);
	glEnd();

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
