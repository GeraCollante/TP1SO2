#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define ATTEMPS 3 

int firmware;
struct sockaddr_in serv_addr;

int run();
int login();
unsigned int string_hash(void *string);
void updateFirmware();
void writeSock(int sockfd, char * cadena);
void recFile(int newsockfd);
char * readSock(int sockfd);
void handleConnection(int newsockfd);
void createSocketTCP();

#endif /* SERVER_H */