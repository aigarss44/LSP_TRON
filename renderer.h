#pragma once

#include <GL/glut.h>
#include <stdio.h>

#include "gameObjects.h"

#define WINDOW_WIDTH 800	//loga izmēri
#define WINDOW_HEIGHT 450

void Draw(void);
void init_renderer();
void RenderField(Field *field);
