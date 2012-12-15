#include "userInput.h"
#include "gameLogic.h"

void MouseButtonPressed(int button, int state, int x, int y)
{
  printf("MouseButtonPressed %i state %i x %i y %i\n",button, state, x ,y);
}

void MouseMotion(int x, int y)
{
  printf("MouseMotion x %i y %i\n",x ,y);
}

void KeyboardKeyPressed(unsigned char key, int x, int y)
{
  printf ("KeyboardKeyPressed %c x %i y %i\n", key, x, y);
}