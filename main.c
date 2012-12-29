#include "gameLogic.h"
#include "network.h"
#include "renderer.h"
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
	const char *ver = glGetString(GL_VERSION);

	InitGame();
	InitGraphics(argc,argv);
	InitInput();
	glutIdleFunc (gameTick);

	printf("%s\n", ver);
	init_renderer();

	glutMainLoop();
	return 0;
}
