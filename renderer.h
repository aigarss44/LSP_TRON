#pragma once

#include <GL/glut.h>
#include <stdio.h>

#include "gameObjects.h"

void Draw(void);
void init_renderer();
void RenderField(Field *field);
