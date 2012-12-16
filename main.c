#include "gameLogic.h"
#include "network.h"
#include "renderer.h"
#include "userInput.h"

#ifndef GLUT_H
#define GLUT_H
#include <gl/glut.h>
#endif // !GLUT_H

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif // !STDIO_H

#define WINDOW_WIDTH 800	//loga izmēri
#define WINDOW_HEIGHT 450

void InitInput() {
	glutKeyboardFunc (KeyboardKeyPressed);
	glutMouseFunc (MouseButtonPressed);
	glutMotionFunc (MouseMotion);
}

void InitGraphics(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowPosition(50,50);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutCreateWindow("TRON");
	glutDisplayFunc(Draw);
}

int main(int argc, char **argv) {

	InitGame();
	InitGraphics(argc,argv);
	InitInput();
	glutIdleFunc (gameTick);
	glutMainLoop();
	return 0;
}
