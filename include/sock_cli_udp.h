/** @file module.h
 * 
 * @brief A description of the module’s purpose. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Barr Group.  All rights reserved.
 */ 

#ifndef CLIUDP_H
#define CLIUDP_H

#define PORT    9000 
#define MAXLINE 1024
#define TAM     1024

void    handleUDP();
int     createSockUDP();
char *  readSockUDP(int sockfd);
void    sendInfo(int sockfd);

#endif /* CLIUDP_H */

/*** end of file ***/