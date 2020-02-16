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


int create_client_socket(int port, char* ipaddr){
    int l;
	int sfd;
    
	sfd = socket(AF_INET,SOCK_DGRAM,0);
	if (sfd == -1){
        perror("socket fail");
        return EXIT_FAILURE;
	}
    
    // preparation of the destination socket address
	l=sizeof(struct sockaddr_in);
	bzero(&servaddr,l);
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(port);
    if (inet_pton(AF_INET,ipaddr,&servaddr.sin_addr)==0){
		printf("Invalid IP adress\n");
		return EXIT_FAILURE;
	}
    
    return sfd;
}

void readUDP(int sockfd){
	char buffer[MAXLINE];
	socklen_t server_addr_len;
	// printf("Información recibida: \n");
	memset(buffer, '\0', MAXLINE);
	recvfrom(sockfd, (char*)buffer, MAXLINE, 
	0, (struct sockaddr*)&servaddr, 
	&server_addr_len); 
	printf("%s", buffer);
}

int main() 
{ 
    int sockfd;
    char buffer[MAXLINE];
    char* message = "Hello Server";
  
	// socklen_t server_addr_len;
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
				// sockfd = crearSocketUDP();
				// sockfd = create_client_socket(PORT, "192.168.0.31");
				sockfd = create_client_socket(PORT, "169.254.237.70");
				sendto(sockfd, (const char*)message, strlen(message), 
				0, (const struct sockaddr*)&servaddr, 
				sizeof(servaddr));
				// receive server's response 
				// Model
				readUDP(sockfd);
				// Kernel Version
				readUDP(sockfd);
				// Uptime
				readUDP(sockfd);
				// sysTime
				readUDP(sockfd);
				// userTime
				readUDP(sockfd);
				// idleTime
				readUDP(sockfd);
				// freeMem
				readUDP(sockfd);
				// totalMem
				readUDP(sockfd);
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