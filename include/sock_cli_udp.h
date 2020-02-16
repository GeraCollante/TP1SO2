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

#define MAXLINE     1024
#define TAM         1024
#define BUFFSIZE    256

int     crearSocketUDP();
void    showCpuinfo(int);
void    showVersion(int);
int     showUptime(int);
void    showStats(int);
void    showMeminfo(int);
void    uptimeSystemDate();
void    findStr(char *, char *, char *);

#endif /* CLIUDP_H */

/*** end of file ***/