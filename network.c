#include "network.h"
#include <stdio.h>
#include <string.h>

#include "serveris/packets.h"

#include <sys/socket.h>
#include <netinet/in.h>

int sock = -1;

void _joingame();
void _leavegame();
void _senddata();

int hostGame() {	//bus jaatgriezh 0 ja success. pasha funkcija bus janolasa dati no kaut kada konfig faila.
	printf("hostGame\n");
	fflush(0);

	return 0;
}
int joinGame() {   //bus jaatgriezh dati, kas dara zinamus speles parametrus (lauka izmers, framerate utt)
	printf("joinGame\n");
	fflush(0);

	_joingame();

	return 0;
}
int leaveGame() {   //ari jaatgriezh 0 ja success
	printf("leaveGame\n");
	fflush(0);

	_leavegame();

	return 0;
}
int dataRecieved() {   //shitam butu jaizsaucas tik reizes sekunde kads ir servera noteiktais framerate
	printf("dataRecieved\n");
	fflush(0);

	updateGameFromServer(12345);    //kad bus savienojums ar serveri tad sacepsim datu strukturu ko te padot. pagaidam viens integeris tikai lai redzams ka viss strada ka nakas.
	return 0;
}
int sendData(int testVar) {    //uzliku lai shitas izsaucas katru reizi kad tu pagriezies
	printf("sendData: %i\n", testVar);	//padodu 1 ja pa labi 2 ja pa kreisi. shitas ari tikai testeshanai
	fflush(0);

	_senddata();

	return 0;
}

/************ JOIN GAME ***************/
void create_connection(char *address, char *port);
void send_join();
void _joingame() {

	char address[15] = {0};
	char port[4] = {0};

	FILE *file = fopen(".config", "r");
	fscanf(file, "ip=%s\nport=%s", address, port);
	fclose(file);

	printf("ip: %s\n", address);
	printf("port: %s\n", port);

	create_connection(address, port);
}
void create_connection(char *address, char *port) {

	sock = socket(AF_INET, SOCK_STREAM, 0);
	printf("socket: %d\n", sock);

	struct sockaddr_in conn;
	memset(&conn, 0, sizeof(struct sockaddr_in));
	conn.sin_addr.s_addr = inet_addr(address);
	conn.sin_family = AF_INET;
	conn.sin_port = htons(atoi(port));

	int err = connect(sock, (struct sockaddr *)&conn, sizeof(struct sockaddr_in));
	printf("connection: %d\n", err);

	send_join();
}
void send_join() {

	struct Header h = {PCKT_CONNECTION_REQUEST, 0};
	int err = send(sock, &h, sizeof(struct Header), 0);
	printf("sent: %d\n", err);

	char reply[4096] = {0};

	err = recv(sock, reply, sizeof(reply), 0);
	printf("received: %d\n", err);

	struct Header *rh = (struct Header *)&reply[0];
	struct ConnectionResponse *r = (struct ConnectionResponse *)&reply[sizeof(struct Header)];
	printf("reply type: %d\n", (int)rh->type);
	printf("reply length: %d\n", rh->length);

}
/**************************************/

/************ LEAVE GAME **************/
void _leavegame() {
	close(sock);
}
/**************************************/

/************* SEND DATA **************/
void _senddata() {

	int size = sizeof(struct Header) + sizeof(struct EventPlayer);
	char *msg = (char *)malloc(size);

	struct Header *h = (struct Header *)&msg[0];
	struct EventPlayer *e = (struct EventPlayer *)&msg[sizeof(struct Header)];

	h->type = PCKT_EVENT;
	h->length = sizeof(struct EventPlayer);

	e->direction = MOVE_FORWARD;
	e->shot = 0;

	int err = send(sock, msg, size, 0);
	printf("event sent: &d\n", err);

	free(msg);
}
/**************************************/

/*********** RECEIVE DATA *************/
void _receivedata() {

}
/**************************************/


























