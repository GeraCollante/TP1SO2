// TCP Client program 
#include <arpa/inet.h> 
#include <errno.h> 
#include <netinet/in.h> 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <sys/time.h>
#include <netdb.h> 
#include <time.h>
#include <fcntl.h>
#include "sock_srv_tcp.h"
#include "sock_srv_udp.h"

#define UFB 	75684438
#define SS 		2127732462
#define OT 		2104739370
#define HELP 	1950366504
#define EXIT 	258360873

int main() 
{ 
    int sockfd;
    char buffer[MAXLINE];
    char* message = "Hello Server";
  
    int n, len;
	int salir = 0;

	// if(logSuccess()==1)
	if(1)
	{
		do
		{
			printf("Ingrese comando:\n");
			memset(buffer, '\0', MAXLINE);
			fgets(buffer, MAXLINE-1, stdin);

			switch(string_hash(buffer))
			{
			case SS:
				printf("SS\n");
				sockfd = crearSocketTCP();
				actualizarFirmware(sockfd);
				close(sockfd);
				break;
			case UFB:
				printf("UFB\n");
				sockfd = crearSocketTCP();
				startScanning(sockfd);
				close(sockfd);
				break;
			case OT:
				sockfd = crearSocketUDP();
				sendto(sockfd, (const char*)message, strlen(message), 
				0, (const struct sockaddr*)&servaddr, 
				sizeof(servaddr));
				// receive server's response 
				printf("Información recibida: \n");
				memset(buffer, '\0', MAXLINE);
				n = recvfrom(sockfd, (char*)buffer, MAXLINE, 
				0, (struct sockaddr*)&servaddr, 
				&len); 
				printf("%s", buffer);
				close(sockfd);
				break;
			case EXIT:
				salir=1;
			default:
				break;
			}
		}while(salir==0);
	}
	else exit(0);

	return 0;
} 