#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h> 
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int firmware;
struct sockaddr_in serv_addr;

void updateFirmware();
void writeSock(int sockfd, char * cadena);
void recFile(int newsockfd);
char * readSock(int sockfd);
void handleConnection(int newsockfd);
void createSocketTCP();

#endif /* SERVER_H */