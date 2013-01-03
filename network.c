#include "network.h"

int hostGame() {	//bus jaatgriezh 0 ja success. pasha funkcija bus janolasa dati no kaut kada konfig faila.
	printf("hostGame");
	return 0;
}

int joinGame() {   //bus jaatgriezh dati, kas dara zinamus speles parametrus (lauka izmers, framerate utt)
	printf("joinGame");
	return 0;
}

int leaveGame() {   //ari jaatgriezh 0 ja success
	printf("leaveGame");
	return 0;
}

int dataRecieved() {   //shitam butu jaizsaucas tik reizes sekunde kads ir servera noteiktais framerate
	printf("dataRecieved");
	updateGameFromServer(12345);    //kad bus savienojums ar serveri tad sacepsim datu strukturu ko te padot. pagaidam viens integeris tikai lai redzams ka viss strada ka nakas.
	return 0;
}

int sendData(int testVar) {    //uzliku lai shitas izsaucas katru reizi kad tu pagriezies
	printf("sendData: %i", testVar);	//padodu 1 ja pa labi 2 ja pa kreisi. shitas ari tikai testeshanai
	return 0;
}