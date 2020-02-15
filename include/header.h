/** @file module.h
 * 
 * @brief A description of the module’s purpose. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Barr Group.  All rights reserved.
 */ 

#ifndef MODULE_H
#define MODULE_H

#include <arpa/inet.h> 
#include <ctype.h>
#include <errno.h> 
#include <fcntl.h>
#include <ifaddrs.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <strings.h>
#include <sys/socket.h> 
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h> 
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include "funciones.h"

#define PORT    6682
#define MAXLINE 1024 
#define BUFFER  1024 

struct sockaddr_in cliaddr, servaddr;

// #define PORT 5000
// #define TAM 256
// #define BUFFER 1500
// #define MAXLINE 1500

#endif /* MODULE_H */

/*** end of file ***/