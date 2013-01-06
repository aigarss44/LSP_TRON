/* 
 * File:   worker.c
 * Author: FlutterCanon
 *
 * Created on January 5, 2013, 1:17 PM
 * 
 * Strâdnieks, kas apkalpos vienu klientu.
 */

#include "worker.h"
#include"packets.h"

#include <stdio.h>
#include <stdlib.h>
#include<string.h>	//strlen
#include<stdlib.h>	//strlen

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
        size_t packet_size = sizeof(*head), head_size = sizeof(*head);
        int packet_type;
        struct ConnectionRequest *request = (struct ConnectionRequest*)malloc(sizeof(*request));
        struct ConnectionResponse *rResp = (struct ConnectionResponse*)malloc(sizeof(*rResp));
        
        
        
        while (1) {
                //Receive a message from client
                if( (read_size = recv(sock , head , packet_size , 0)) > 0 )
                {
                        printf("size: %d\n", head->length);
                        //packet_size = ntohl(head->length);
                        packet_size = head->length;
                        printf("packet size = %d\n", packet_size);
                        packet_type = head->type;
                        if( (read_size = recv(sock , request , packet_size , 0)) == 0 )
                        {
                                rResp->id = htonl(5);               // Izsniegtais ID
                                rResp->height = htonl(5);           // Spçles laukuma augstums >= 30
                                rResp->width = htonl(5);            // Spçles laukuma platums >= 80
                                rResp->playerCount = htonl(5);      // Spçlçtâju daudzums (vajadzîgs ?)
                                rResp->tailLength = htonl(5);       // Astes garums (vajadzîgs ?)
                                rResp->frameRate = htonl(5);        // Kadri sekundç
                                rResp->bulletSpeed = htonl(5);      // Lodes âtrums (kadros)
                                rResp->bulletCooldown = htonl(5);   // Lodes cooldowns (kadros)
                                rResp->timeout = htonl(5);          // ??
                                head->type = PCKT_CONNECTION_RESPONSE;
                                next_size = sizeof(*rResp);
                                printf("size of resp: %d\n", next_size);
                                //head->length = htonl(36);
                                head->length = next_size;
                                
                                //Send some data
                                printf("Pakas tips: %d, pakas izmçrs: %d\n", head->type, head->length);
                                if( send(sock , head , head_size , 0) < 0)
                                {
                                        puts("Sent failed.");
                                        //exit(1);
                                }
                        }
                        printf("read size: %d\n", read_size);
                }
                if(read_size == -1)
                {
                        perror("recv failed");
                }
        }
		
	//Free the socket pointer
	free(socket_desc);
        free(head);
        free(request);
	
	return 0;
}

