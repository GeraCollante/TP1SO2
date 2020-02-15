#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 50
#define SIZE 10000
char lreg[SIZE][MATRIX_SIZE];

int     max(int , int );
void 	clrReg(char (*pointer)[MATRIX_SIZE]);
void 	loadReg(char (*pointer)[MATRIX_SIZE], char * ptr);
void 	loadReg2(char (*pointer)[MATRIX_SIZE], char * ptr);
void 	listar(char (*pointer)[MATRIX_SIZE]);
char * 	find(char (*pointer)[MATRIX_SIZE], char * buscar);
int 	returnPos(char (*pointer)[MATRIX_SIZE], char * buscar);
int 	countNoNull(char (*pointer)[MATRIX_SIZE]);
char * 	file2Str(FILE *fp);
char * 	file2Str2(FILE *fp);

#endif /* FUNCIONES_H_ */
