#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <time.h>
#include <fcntl.h>

struct sockaddr_in serv_addr;
int firmware;

void setFirmware();
void writeSock(int sockfd, char * str);
char * readSock(int sockfd);
void recFile(int newsockfd);
void sendFile(int sockfd, char * filename);
void handleConnection(int sockfd);
void createSockTCP();

#endif /* CLIENTE_H */