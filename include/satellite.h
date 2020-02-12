/** @file module.h
 * 
 * @brief A description of the module’s purpose. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Barr Group.  All rights reserved.
 */ 

#ifndef SATELLITE_H
#define SATELLITE_H

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <time.h>

#define TAM 1024
#define STR 128

struct satellite{
   char  id[STR];
   char  uptime[STR];
   char  version[STR];
   char  mem[STR];
   char  cpu[STR];
};

void    loadInfoSat();
char *  id();
char *  version();
char *  UpTime();
char *  secondsToDHMS(int sec);
char *  CPU();
char *  mem();
char *  infoSatellite();

#endif /* SATELLITE_H */

/*** end of file ***/