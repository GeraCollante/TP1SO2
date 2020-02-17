// TCP Client program 
#include "sock_srv_tcp.h"
#include "sock_srv_udp.h"

#define UFB 	75684438
#define SS 		2127732462
#define OT 		2104739370
#define HELP 	1950366504
#define EXIT 	258360873

/**
 * @brief Creación del server
 * 
 */
void server(){
	int sockfd;
    char buffer[MAXLINE];
    char* message = "Hello Server";
  
	int salir = 0;

	if(logSuccess()==1)
	// if(1)
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
				sockfd = crearSocketUDP(PORT, "169.254.237.70");
				sendto(sockfd, (const char*)message, strlen(message), 
				0, (const struct sockaddr*)&servaddr, 
				sizeof(servaddr));
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
}

int main() 
{ 
    server();

	return 0;
} 