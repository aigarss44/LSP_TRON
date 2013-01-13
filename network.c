#include "network.h"
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include "gameLogic.h"

#include "packets.h"


int sock = -1;
pthread_t tid;

void *_joingame(void *arg);
void _leavegame();
void _senddata();
void _receivedata();

int hostGame() {	//bus jaatgriezh 0 ja success. pasha funkcija bus janolasa dati no kaut kada konfig faila.
	printf("hostGame\n");
	fflush(0);

	return 0;
}
int joinGame() {   //bus jaatgriezh dati, kas dara zinamus speles parametrus (lauka izmers, framerate utt)
	printf("joinGame\n");
	fflush(0);

	pthread_create(&tid, 0, _joingame, 0);

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
void *_joingame(void *arg) {

	char address[15] = {0};
	char port[4] = {0};

	FILE *file = fopen(".config", "r");
	fscanf(file, "ip=%s\nport=%s", address, port);
	fclose(file);

	printf("ip: %s\n", address);
	printf("port: %s\n", port);

	create_connection(address, port);
	return 0;
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
void send_join(void *arg) {

	struct Header h = {PCKT_CONNECTION_REQUEST, 0};
	int err = write(sock, &h, sizeof(struct Header));
	printf("sent: %d\n", err);

	struct Header hr;
	struct ConnectionResponse cr;

	err = read(sock, &hr, sizeof(struct Header));
		printf("received: %d\n", err);

	err = read(sock, &cr, hr.length);
		printf("received: %d\n", err);

	printf("reply type: %d\n", (int)hr.type);
	printf("reply length: %d\n", hr.length);

	receivedGameSettings(&cr);

	_receivedata();
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
	printf("event sent: %d\n", err);

	free(msg);
}
/**************************************/

/*********** RECEIVE DATA *************/

struct Header h;
struct UpdatePlayerHeader uph;
struct UpdatePlayer up;
struct UpdateBulletHeader ubh;
struct UpdateBullet ub;
struct UpdateTotalTailHeader utth;
struct UpdateTailHeader uth;
struct UpdateTail ut;

void readpack(void *dst, size_t size) {
	//int err = recv(sock, dst, size, 0);
	int err = read(sock, dst, size);
	if (err < 0)
		printf("readpack error");
}
void read_Header() {
	readpack(&h, sizeof(struct Header));
	h.length = ntohl(h.length);
}
void read_UpdatePlayerHeader() {
	readpack(&uph, sizeof(struct UpdatePlayerHeader));
	uph.playerCount = ntohl(uph.playerCount);
}
void read_UpdatePlayer() {
	readpack(&up, sizeof(struct UpdatePlayer));
	up.cooldown = ntohl(up.cooldown);
	up.direction = ntohl(up.direction);
	up.gameover = ntohl(up.gameover);
	up.id = ntohl(up.id);
	up.x = ntohl(up.x);
	up.y = ntohl(up.y);
}
void read_UpdateBulletHeader() {
	readpack(&ubh, sizeof(struct UpdateBulletHeader));
	ubh.bulletCount = ntohl(ubh.bulletCount);
}
void read_UpdateBullet() {
	readpack(&ub, sizeof(struct UpdateBullet));
	ub.direction = ntohl(ub.direction);
	ub.id = ntohl(ub.id);
	ub.x = ntohl(ub.x);
	ub.y = ntohl(ub.y);
}
void read_UpdateTotalTailHeader() {
	readpack(&utth, sizeof(struct UpdateTotalTailHeader));
	utth.totalTailLength = ntohl(utth.totalTailLength);
}
void read_UpdateTailHeader() {
	readpack(&uth, sizeof(struct UpdateTailHeader));
	uth.id = ntohl(uth.id);
	uth.tailCount = ntohl(uth.tailCount);
}
void read_UpdateTail() {
	readpack(&ut, sizeof(struct UpdateTail));
	ut.x = ntohl(ut.x);
	ut.y = ntohl(ut.y);
}
void read_Update() {

	UpdatePackage upack;

	read_Header();
	if (h.type != PCKT_UPDATE)
		printf("wrong package on update");

	int i = 0;

	read_UpdatePlayerHeader();
	upack.player_count = uph.playerCount;
	for (i = 0; i < uph.playerCount; i++) {
		read_UpdatePlayer();
		//ierakstit datus kkada tabulaa
		upack.players[i] = up;
	}

	read_UpdateTotalTailHeader();
	upack.total_tail_length = utth.totalTailLength;
	for (i = 0; i < utth.totalTailLength; i++) {
		int j;
		read_UpdateTailHeader();
		upack.tails[i].uth = uth;
		for (j = 0; j < uth.tailCount; j++) {
			read_UpdateTail();
			upack.tails[i].ut[j] = ut;
		}
	}

	read_UpdateBulletHeader();
	upack.bullet_count = ubh.bulletCount;
	upack.ub = (struct UpdateBullet *)malloc(sizeof(struct UpdateBullet) * ubh.bulletCount);
	for (i = 0; i < ubh.bulletCount; i++) {
		read_UpdateBullet();
		//ierakstit datus kkadas tabulaa
		upack.ub[i] = ub;
	}

	receivedUpdate(&upack);
	free(upack.ub);
}
void _receivedata() {
	while (1) {
		read_Update();
	}
}
/**************************************/


























