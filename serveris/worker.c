/* 
 * File:   worker.c
 * Author: FlutterCanon
 *
 * Created on January 5, 2013, 1:17 PM
 * 
 * Str�dnieks, kas apkalpos vienu klientu.
 */

#include "worker.h"
#include"packets.h"

#include <stdio.h>
#include <stdlib.h>
#include<string.h>	//strlen
#include<stdlib.h>	//strlen

//Ieg�stam datus par to cik lietot�ju updeiti b�s j�s�ta un sagatavojam tos
void getPHead(struct UpdatePlayerHeader *pHead)
{
    pHead->playerCount = htonl(3);
}


//Ieg�stam datus par pirmo responsi un sagatavojam tos
void getrResp(struct ConnectionResponse *rResp)
{
    rResp->id = htonl(5);               // Izsniegtais ID
    rResp->height = htonl(5);           // Sp�les laukuma augstums >= 30
    rResp->width = htonl(5);            // Sp�les laukuma platums >= 80
    rResp->playerCount = htonl(5);      // Sp�l�t�ju daudzums (vajadz�gs ?)
    rResp->tailLength = htonl(5);       // Astes garums (vajadz�gs ?)
    rResp->frameRate = htonl(5);        // Kadri sekund�
    rResp->bulletSpeed = htonl(5);      // Lodes �trums (kadros)
    rResp->bulletCooldown = htonl(5);   // Lodes cooldowns (kadros)
    rResp->timeout = htonl(5);          // ??
}

//Ieg�stam datus par k�rt�jo sp�l�t�ju un sagatavojam tos
void getPUpdate(struct UpdatePlayer * pUpdate)
{
    pUpdate->id = htonl(11);
    pUpdate->x = htonl(11);
    pUpdate->y = htonl(11);
    pUpdate->direction = htonl(11);
    pUpdate->cooldown = htonl(11);
    pUpdate->gameover = htonl(11);
}

//Ieg�stam datus par to cik lodes b�s un sagatavojam tos
void getBHead(struct UpdateBulletHeader *pHead) 
{
    pHead->bulletCount = htonl(4);
}

//Ieg�stam datus par k�rt�jo lodi un sagatavojam tos
void getBUpdate(struct UpdateBullet * bUpdate)
{
    bUpdate->id = htonl(66);
    bUpdate->x = htonl(66);
    bUpdate->y = htonl(66);
    bUpdate->direction = htonl(66);
}

//Nos�tam hedu par n�kamo paku
void sendHead(int sock, struct Header *head) 
{
    size_t head_size = sizeof(*head);
    puts("Sending head.");
    if( send(sock , head , head_size , 0) < 0)
        {
                puts("Sent failed.");
                //exit(1);
        }
    puts("Head Sent.");
}

//Nos�ta k�rt�jo update klientam
void sendClientUpdate(int sock, struct Header *head) 
{
    
    struct UpdatePlayerHeader *pHead = (struct UpdatePlayerHeader*)malloc(sizeof(*pHead));
    struct UpdatePlayer *pUpdate = (struct UpdatePlayer*)malloc(sizeof(*pUpdate));
    struct UpdateBulletHeader *bHead = (struct UpdateBulletHeader*)malloc(sizeof(*bHead));
    struct UpdateBullet *bUpdate = (struct UpdateBullet*)malloc(sizeof(*bUpdate));
    uint32_t next_size;
    int forW = 0;
    
    getPHead(pHead);
    head->type = PCKT_UPDATE;
    next_size = sizeof(*pHead);
    head->length = htonl(next_size);
    sendHead(sock, head);
    if( send(sock , pHead , next_size , 0) < 0)
        {
                puts("Sent failed.");
                //exit(1);
        }
    for(forW = 0; forW < ntohl(pHead->playerCount); forW++) {
        getPUpdate(pUpdate);
        head->type = PCKT_UPDATE;
        next_size = sizeof(*pUpdate);
        head->length = htonl(next_size);
        sendHead(sock, head);
        if( send(sock , pUpdate , next_size , 0) < 0)
            {
                    puts("Sent failed.");
                    //exit(1);
            }
    }
    getBHead(bHead);
    head->type = PCKT_UPDATE;
    next_size = sizeof(*bHead);
    head->length = htonl(next_size);
    sendHead(sock, head);
    if( send(sock , bHead , next_size , 0) < 0)
        {
                puts("Sent failed.");
                //exit(1);
        }
    for(forW = 0; forW < ntohl(bHead->bulletCount); forW++) {
        getBUpdate(bUpdate);
        head->type = PCKT_UPDATE;
        next_size = sizeof(*bUpdate);
        head->length = htonl(next_size);
        sendHead(sock, head);
        if( send(sock , bUpdate , next_size , 0) < 0)
            {
                    puts("Sent failed.");
                    //exit(1);
            }
    }
    
    free(pHead);
    free(pUpdate);
    free(bHead);
    free(bUpdate);
}

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
	//Get the socket descriptor
	int sock = *(int*)socket_desc;
	int read_size;
        uint32_t next_size;
        struct Header *head = (struct Header*)malloc(sizeof(*head));
        size_t packet_size = sizeof(*head);
        int packet_type;
        
        struct ConnectionRequest *request = (struct ConnectionRequest*)malloc(sizeof(*request));
        struct ConnectionResponse *rResp = (struct ConnectionResponse*)malloc(sizeof(*rResp));
        
        
        //Sa�emam zi�u no klienta
        if( (read_size = recv(sock , head , packet_size , 0)) > 0 )
        {
                packet_size = ntohl(head->length);
                packet_type = head->type;
                //Nos�tam pirmo responsu
                if( packet_type == PCKT_CONNECTION_REQUEST )
                {
                        getrResp(rResp);
                        head->type = PCKT_CONNECTION_RESPONSE;
                        next_size = sizeof(*rResp);
                        head->length = htonl(next_size);

                        //Send some data
                        sendHead(sock, head);
                        if( send(sock , rResp , next_size , 0) < 0)
                        {
                                puts("Sent failed.");
                                //exit(1);
                        }

                }
        }
        
        sendClientUpdate(sock, head);
	//Free the socket pointer
        puts("Worker ending.");
	free(socket_desc);
        free(head);
        free(request);
        free(rResp);
	
	return 0;
}

