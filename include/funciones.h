#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 50
#define SIZE 10000
char lreg[SIZE][MATRIX_SIZE];

//Limpiar lista
void clrReg(char (*pointer)[MATRIX_SIZE]){
	for(int k = 0; k<SIZE;k++){
	strcpy(pointer[k],"");
	}
}

//Tokenizar por "\n:"
void loadReg(char (*pointer)[MATRIX_SIZE], char * ptr)
{
	clrReg(lreg);
	int k = 0;
	char *pch;
	pch = strtok (ptr,"\n:");
	while (pch != NULL)
	{
		strcpy(pointer[k],pch);
	    pch = strtok (NULL, "\n:");
	    k++;
	    if(k>SIZE)
		{
	    	break;
		}
	}
}

//Tokenizar por "\n: "
void loadReg2(char (*pointer)[MATRIX_SIZE], char * ptr)
{
	clrReg(lreg);
	int k = 0;
	char *pch;
	pch = strtok (ptr,"\n: ");
	while (pch != NULL)
	{
		strcpy(pointer[k],pch);
	    pch = strtok (NULL, "\n: ");
	    k++;
	    if(k>SIZE)
		{
	    	break;
		}
	}
}

//Listar todos los elementos de la lista
void listar(char (*pointer)[MATRIX_SIZE]){
	for(int j=0; j<SIZE;j++){
		printf("%d",j);
		puts(pointer[j]);
	}
}

//Encontrar una palabra y devolver la siguiente
char * find(char (*pointer)[MATRIX_SIZE], char * buscar)
{
	for(int i = 0; i < SIZE; ++i)
		{
			if (strstr(pointer[i], buscar) != NULL)
			{
				return pointer[i+1];
				break;
			}
		}
	return NULL;
}

//Devolver pocisión de un caracter especifico
int returnPos(char (*pointer)[MATRIX_SIZE], char * buscar)
{
	for(int i = 0; i < SIZE; ++i)
		{
			if (strstr(pointer[i], buscar) != NULL)
			{
				return i;
				break;
			}
		}
	return -1;
}

//Contar cantidad de palabras no nulas
int countNoNull(char (*pointer)[MATRIX_SIZE])
{
	int counter=0;
	for(int i = 0; i < SIZE; ++i)
		{
			if (strcmp(pointer[i],"")!=0)
			{
				counter++;
			}
		}
	return counter;
}

//Cargar lista con un file determinado
char * file2Str(FILE *fp)
{
	size_t size = 0;
	char *reg=0;
	while(getdelim(&reg, &size, 0, fp) != -1)
		{
		}
	return reg;
}

//Cargar lista con un file determinado
char * file2Str2(FILE *fp){
	char str[SIZE];
	char *ptr;
	ptr = str;
	while (fgets(str, SIZE, fp) != NULL)
	{}
	return ptr;
}

#endif /* FUNCIONES_H_ */
