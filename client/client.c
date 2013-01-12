/* 
 * File:   client.c
 * Author: FlutterCanon
 *
 * Created on January 6, 2013, 9:48 AM
 */
#include"packets.h"

#include<stdio.h>	//printf
#include<string.h>	//strlen
#include<sys/socket.h>	//socket
#include<arpa/inet.h>	//inet_addr
#include <stdlib.h>
#include <unistd.h>

//Apstrâdâ Response struktûru
void workResponse(struct ConnectionResponse * rResp) {
    rResp->id = ntohl(rResp->id);               // Izsniegtais ID
    rResp->height = ntohl(rResp->height);           // Spçles laukuma augstums >= 30
    rResp->width = ntohl(rResp->width);            // Spçles laukuma platums >= 80
    rResp->playerCount = ntohl(rResp->playerCount);      // Spçlçtâju daudzums (vajadzîgs ?)
    rResp->tailLength = ntohl(rResp->tailLength);       // Astes garums (vajadzîgs ?)
    rResp->frameRate = ntohl(rResp->frameRate);        // Kadri sekundç
    rResp->bulletSpeed = ntohl(rResp->bulletSpeed);      // Lodes âtrums (kadros)
    rResp->bulletCooldown = ntohl(rResp->bulletCooldown);   // Lodes cooldowns (kadros)
    rResp->timeout = ntohl(rResp->timeout);          // ??
    //Dati atjaunoti
    //Tagad var apstrâdât tâlâk
    printf("id: %d\nheight: %d\nwidth: %d\nplayerCount: %d\ntailLenght: %d\nframeRate: %d\nbulletSpeed: %d\nbulletCooldown: %d\ntimeout: %d\n", rResp->id, rResp->height, rResp->width, rResp->playerCount, rResp->tailLength, rResp->frameRate, rResp->bulletSpeed, rResp->bulletCooldown, rResp->timeout);

}

//Apstrâdâ spçlçtâju hederi
void workPHead(struct UpdatePlayerHeader *pHead) 
{
    pHead->playerCount = ntohl(pHead->playerCount);
    printf("Player count: %d\n", pHead->playerCount);
}

//Apstrâdâ konkrçta spçlçtâja updeitu
void workPUpdate(struct UpdatePlayer * pUpdate)
{
    pUpdate->id = ntohl(pUpdate->id);
    pUpdate->x = ntohl(pUpdate->x);
    pUpdate->y = ntohl(pUpdate->y);
    pUpdate->direction = ntohl(pUpdate->direction);
    pUpdate->cooldown = ntohl(pUpdate->cooldown);
    pUpdate->gameover = ntohl(pUpdate->gameover);
    printf("id: %d\nx: %d\ny: %d\ndirection: %d\ncooldown: %d\ngameover: %d\n", pUpdate->id, pUpdate->x, pUpdate->y, pUpdate->direction, pUpdate->cooldown, pUpdate->gameover);
}

//Apstrâdâ loþu hederi
void workBHead(struct UpdateBulletHeader *pHead) 
{
    pHead->bulletCount = ntohl(pHead->bulletCount);
    printf("Player count: %d\n", pHead->bulletCount);
}

//Apstrâdâ loþu updeitu
void workBUpdate(struct UpdateBullet * bUpdate)
{
    bUpdate->id = ntohl(bUpdate->id);
    bUpdate->x = ntohl(bUpdate->x);
    bUpdate->y = ntohl(bUpdate->y);
    bUpdate->direction = ntohl(bUpdate->direction);
    printf("id: %d\nx: %d\ny: %d\ndirection: %d\n", bUpdate->id, bUpdate->x, bUpdate->y, bUpdate->direction);
}

//Saòem nâkamâs pakas hederi
void receiveHead(int sock, struct Header *head) 
{
    size_t head_size = sizeof(*head);
    puts("Waiting head.");
    if( recv(sock , head , head_size , 0) < 1)
    {
            puts("Receiving failed.");
            exit(1);
    }

    puts("Head received.");
    head->length = ntohl(head->length);
    printf("Pakas tips: %d, pakas izmers: %d\n", head->type, head->length);
}

int main(int argc , char *argv[])
{
	int sock;
        int forW = 0;
	struct sockaddr_in server;
        struct Header *head = (struct Header*)malloc(sizeof(*head));
        struct ConnectionRequest *request = (struct ConnectionRequest*)malloc(sizeof(*request));
        struct ConnectionResponse *rResp = (struct ConnectionResponse*)malloc(sizeof(*rResp));
        struct UpdatePlayerHeader *pHead = (struct UpdatePlayerHeader*)malloc(sizeof(*pHead));
        struct UpdatePlayer *pUpdate = (struct UpdatePlayer*)malloc(sizeof(*pUpdate));
        struct UpdateBulletHeader *bHead = (struct UpdateBulletHeader*)malloc(sizeof(*bHead));
        struct UpdateBullet *bUpdate = (struct UpdateBullet*)malloc(sizeof(*bUpdate));
        struct EventPlayer *pEvent = (struct EventPlayer*)malloc(sizeof(*pEvent));
        size_t head_size = sizeof(*head);
        
     
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		perror("Can't create socket.");
                exit(1);
	}
	puts("Socket created.");
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("Can't connect.");
		return 1;
	}
	
	puts("Connected.");
        
        //Nosûtam pirmo hedu
        puts("Sending initial request head.");
        head->type = PCKT_CONNECTION_REQUEST;
        head->length = htonl(0);
        
        puts("Sending head.");
        if( send(sock , head , head_size , 0) < 0)
        {
                puts("Sending failed.");
                exit(1);
        }
        puts("Head sent.");
        
        //Kâ nosûtît tukðu stuktûru????
        puts("Sending request- how to send empty req???.");
        //sent = send(sock , request , sizeof(*request) , 0);
/*
        if( sent < 0)
        {
                puts("Sending failed.");
                exit(1);
        }
        puts("Request sent, waiting response.");
*/
        //Ciklojamies saòemot servera updeitus
        while (1) {
            puts("Waiting while first packet.");
            receiveHead(sock, head);
            //Pârbaudam kâda tipa paku saòçmâm
            switch(head->type){
                case 2: //Apstrâdâjam pirmo responsu, kurâ ir dati par spçli
                    if( recv(sock , rResp , head->length , 0) < 0)
                    {
                            puts("Receiving failed.");
                            exit(1);
                    }
                    puts("Packet type 2 received.");
                    workResponse(rResp);
                    break;
                case 3: //Apstrâdâjam kârtçjo responsu, kurâ ir dati par jaunâk situâciju
                    if( recv(sock , pHead , head->length , 0) < 0) //Saòemam skaitu cik lietotâju updeiti bûs
                    {
                            puts("Receiving failed.");
                            exit(1);
                    }
                    puts("Packet type 3 received.");
                    workPHead(pHead);
                    //Izejam cauri visiem lietotâju updeitiem
                    for(forW = 0; forW < pHead->playerCount; forW++) {
                        receiveHead(sock, head);
                        if( recv(sock , pUpdate , head->length , 0) < 0)
                        {
                                puts("Receiving failed.");
                                exit(1);
                        }
                        puts("Packet pupdate received.");
                        workPUpdate(pUpdate);
                    }
                    receiveHead(sock, head);
                    if( recv(sock , bHead , head->length , 0) < 0) //Saòemam skait cik lodes bûs
                    {
                            puts("Receiving failed.");
                            exit(1);
                    }
                    puts("Packet received.");
                    workBHead(bHead);
                    //Izejam cauri visâm lodçm
                    for(forW = 0; forW < bHead->bulletCount; forW++) {
                        receiveHead(sock, head);
                        if( recv(sock , bUpdate , head->length , 0) < 0)
                        {
                                puts("Receiving failed.");
                                exit(1);
                        }
                        puts("Packet bupdate received.");
                        workBUpdate(bUpdate);
                    }
                    break;
                default: //Nezinam kas par paku atnâca
                    puts("Unknown packet.");
                    break;
            }
            
        }
	free(head);
        free(request);
        free(rResp);
        free(pHead);
        free(pUpdate);
        free(bHead);
        free(bUpdate);
	close(sock);
	return 0;
}
