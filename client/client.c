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

int main(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server;
        struct Header *head = (struct Header*)malloc(sizeof(*head));
        struct ConnectionRequest *request = (struct ConnectionRequest*)malloc(sizeof(*request));
        size_t packet_size = sizeof(*head), head_size = sizeof(*head);
     
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
        puts("Sending initial request.");
        head->type = PCKT_CONNECTION_REQUEST;
        //head->length = htonl(99);
        head->length = 0;
        printf("garums: %d\n", head->length);

        //Send some data
        puts("Sending head.");
        if( send(sock , head , head_size , 0) < 0)
        {
                puts("Sending failed.");
                exit(1);
        }
        puts("Head sent.");

        puts("Sending request.");
        printf("request size = %d\n", sizeof(*request));
        if( send(sock , request , sizeof(*request) , 0) < 0)
        {
                puts("Sending failed.");
                exit(1);
        }
        puts("Request sent, waiting response.");
        //Receive a reply from the server
        if( recv(sock , head , head_size , 0) < 0)
        {
                puts("Receiving failed.");
                exit(1);
        }

        puts("Answer received.");
	//head->length = ntohl(head->length);
        printf("Pakas tips: %d, pakas izmçrs: %d\n", head->type, head->length);
	//keep communicating with server
	while(1)
	{
            puts("While start.");
            char c;
            c=getchar();
                
                
	}
	free(head);
        free(request);
	close(sock);
	return 0;
}
