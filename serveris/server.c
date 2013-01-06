/* 
 * File:   server.c
 * Author: Oskars
 *
 * Created on December 30, 2012, 3:33 PM
 */
#include"server.h"
#include "worker.h"


#include<stdio.h>
#include<string.h>	//strlen
#include<stdlib.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include<pthread.h> //for threading , link with lpthread


int main(int argc , char *argv[])
{
	int socket_desc , client_sock , c , *new_sock;
	struct sockaddr_in server , client;
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		//print the error message
		perror("Can't create socket.");
		return 1;
	}
	puts("Socket created.");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("Can't bind socket.");
		return 1;
	}
	puts("Socket bind.");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming request...");
	c = sizeof(struct sockaddr_in);
	while( 1 )
	{
                client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
                
		puts("Request received.");
                
                if (client_sock < 0)
                {
                        puts("Can't process request.");
                        //exit(1);
                } 
                else 
                {
                        pthread_t sniffer_thread;
                        new_sock = malloc(1);
                        *new_sock = client_sock;
                        
                        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
                        {
                                puts("Can't create thread.");
                                //exit(1);
                        } else 
                        {
                                //Now join the thread , so that we dont terminate before the thread
                                //pthread_join( sniffer_thread , NULL);
                                puts("Worker assigned, waiting for next request.");
                        }
                }
		
	}
	
	return 0;
}



