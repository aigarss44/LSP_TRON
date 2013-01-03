#include "userInput.h"


void MouseButtonPressed(int button, int state, int x, int y)
{
  //printf("MouseButtonPressed %i state %i x %i y %i\n",button, state, x ,y);
}

void MouseMotion(int x, int y)
{
  //printf("MouseMotion x %i y %i\n",x ,y);
}

void KeyboardKeyPressed(unsigned char key, int x, int y)
{
  //printf ("KeyboardKeyPressed %c x %i y %i\n", key, x, y);

  switch (key)
  {
  case 27:				// escape poga. rub�jam lauk� sp�li
	  exit (0);
	  break;
  case 'a':				// grie�am moci pa kreisi
	  gameField->player->targetRotation += 90.0f;
	  sendData(2);
	  break;
  case 'd':				//grie�am moci pa labi
	  gameField->player->targetRotation -= 90.0f;
	  sendData(1);
	  break;
  case ' ':				// izshaujam lodi
	  //TODO
	  break;


  case 'j':				//joinojamies spelei
	  joinGame();
	  break;
  case 'h':				//hostojam speli
	  hostGame();
	  break;
  case 'l':				//leavojam speli
	  leaveGame();
	  break;
  }

}