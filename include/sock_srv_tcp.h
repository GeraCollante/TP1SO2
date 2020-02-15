#ifndef SERVER_H
#define SERVER_H

#include "header.h"

#define ATTEMPS 3 

// int firmware;
// struct sockaddr_in serv_addr;

void            actualizarFirmware(int);
int             crearSocketTCP();
void            enviarArchivo(int, char *);
int             fileno(FILE *);
const char *    getIP();
int             login();
int             logSuccess();
void            manejarConexionTCP(int, int);
unsigned int    string_hash(void *);
void            recibirArchivo(int, char *);
void            startScanning(int);

#endif /* SERVER_H */