#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <time.h>
#include <fcntl.h>

struct sockaddr_in serv_addr;
struct sockaddr_in cli_addr;
int firmware;

void setFirmware();
void writeSockTCP(int sockfd, char * str);
char * readSockTCP(int sockfd);
void recFile(int newsockfd);
void sendFile(int sockfd, char * filename);
void handleConnection(int sockfd);
int createSockTCP();

#endif /* CLIENTE_H */