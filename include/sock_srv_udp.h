/** @file module.h
 * 
 * @brief A description of the module’s purpose. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Barr Group.  All rights reserved.
 */ 

#ifndef SRVUDP_H
#define SRVUDP_H

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT    9000 
#define MAXLINE 1024 
#define TAM 1024 

void    handleUDP();
int     createSockUDP();
void    recInfo(int sockfd);

#endif /* SRVUDP_H */

/*** end of file ***/