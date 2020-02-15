/** @file module.h
 * 
 * @brief A description of the module’s purpose. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Barr Group.  All rights reserved.
 */ 

#ifndef CLIUDP_H
#define CLIUDP_H

#include "header.h"

// #define PORT    9000
#define MAXLINE 1024
#define TAM     1024

char *  cargarInfoSatelite();
int     crearSocketUDP();
char *  CPU();
char *  id();
char *  idleTime();
char *  sysTime();
char *  secondsToDHMS(int sec);
char *  mem();
char *  UpTime();
char *  userTime();
char *  version();

#endif /* CLIUDP_H */

/*** end of file ***/