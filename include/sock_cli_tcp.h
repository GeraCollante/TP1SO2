#ifndef CLIENTE_H
#define CLIENTE_H

#include "header.h"

int firmware;

int     crearListenTCP();
void    enviarArchivo(int, char *);
void    manejarConexionTCP(int, char);
void    recibirArchivo(int, char *);
void    setFirmware();
void    showFirmware();
void    updateFirmware();

#endif /* CLIENTE_H */