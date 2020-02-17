#include "funciones.h"

/**
 * @brief Max between two numbers
 * 
 * @param x 
 * @param y 
 * @return int 
 */
int max(int x, int y) 
{ 
    int max = (x>y) ? x : y;
    return max;
}

/**
 * @brief Clean list
 * 
 */
void clrReg(char (*pointer)[MATRIX_SIZE]){
	int k;
	for(k = 0; k<SIZE;k++){
	strcpy(pointer[k],"");
	}
}

/**
 * @brief Tokenize by "\n:"
 * 
 * @param ptr 
 */
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

/**
 * @brief Tokenize by "\n: 
 * 
 * @param ptr 
 */
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

/**
 * @brief List all items in the list
 * 
 */
void listar(char (*pointer)[MATRIX_SIZE]){
	int j;
	for(j=0; j<SIZE;j++){
		printf("%d",j);
		puts(pointer[j]);
	}
}

/**
 * @brief Find a word and return the next
 * 
 * @param buscar 
 * @return char* 
 */
char * find(char (*pointer)[MATRIX_SIZE], char * buscar)
{
	int i;
	for(i = 0; i < SIZE; ++i)
		{
			if (strstr(pointer[i], buscar) != NULL)
			{
				return pointer[i+1];
				break;
			}
		}
	return NULL;
}

/**
 * @brief Return position of a specific character
 * 
 * @param buscar 
 * @return int 
 */
int returnPos(char (*pointer)[MATRIX_SIZE], char * buscar)
{
	int i;
	for(i = 0; i < SIZE; ++i)
		{
			if (strstr(pointer[i], buscar) != NULL)
			{
				return i;
				break;
			}
		}
	return -1;
}

/**
 * @brief Count number of non-null words
 * 
 * @return int 
 */
int countNoNull(char (*pointer)[MATRIX_SIZE])
{
	int i, counter=0;
	for(i = 0; i < SIZE; ++i)
		{
			if (strcmp(pointer[i],"")!=0)
			{
				counter++;
			}
		}
	return counter;
}

/**
 * @brief Load list with a certain file
 * 
 * @param fp 
 * @return char* 
 */
char * file2Str(FILE *fp)
{
	size_t size = 0;
	char *reg=0;
	while(getdelim(&reg, &size, 0, fp) != -1)
		{
		}
	return reg;
}

/**
 * @brief Load list with a certain file,
 * 
 * @param fp 
 * @return char* 
 */
char * file2Str2(FILE *fp){
	char str[SIZE];
	char *ptr;
	ptr = str;
	while (fgets(str, SIZE, fp) != NULL)
	{}
	return ptr;
}