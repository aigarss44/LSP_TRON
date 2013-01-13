#include "network.h"
#include "userInput.h"

#include <GL/glut.h>

#include <stdio.h>

void InitInput() {
	glutKeyboardFunc (KeyboardKeyPressed);
	glutMouseFunc (MouseButtonPressed);
	glutMotionFunc (MouseMotion);
}

void InitGraphics(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(400,200);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutCreateWindow("TRON");
	glutDisplayFunc(Draw);
}

int main(int argc, char **argv) {

	char *ver;

	InitGame();
	InitGraphics(argc,argv);
	InitInput();
	glutIdleFunc (gameTick);

	ver = (char *)glGetString(GL_VERSION);
	printf("%s\n", ver);
	init_renderer();

	glutMainLoop();
	return 0;
}
