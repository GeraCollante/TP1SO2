#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <fcntl.h>
#include "header.h"

struct sockaddr_in serv_addr;

void writeSock(int sockfd, char * cadena)
{
	int n;
	char buffer [TAM];
	memset( buffer, '\0', TAM );
	printf("Entre acá\n");
	strcpy(buffer, cadena);
	printf("%s", buffer);
	n = write( sockfd, buffer, strlen(buffer) );
	if ( n < 0 ) {
		perror( "escritura de socket" );
		exit( 1 );
	}
}

char * readSock(int sockfd)
{
	int n;
	char buffer [TAM];
	memset( buffer, '\0', TAM );
	char * ptrBuff;
	int keylen = strlen(buffer) + 1;
	// Copy password into dynamically allocated storage
	ptrBuff = (char*)malloc(keylen * sizeof(char));
	// printf("rdSock");
	// memset( buffer, '\0', TAM );
	n = read( sockfd, buffer, TAM);
	if ( n < 0 ) {
		perror( "lectura de socket" );
		exit( 1 );
	}
	strcpy(ptrBuff, buffer);
	printf("%s", ptrBuff);
    return ptrBuff;
}

void sendFile(int sockfd, char * filename){	
	char buffer[BUFFER];
	int l=sizeof(struct sockaddr_in);
    off_t count=0, m,sz;//long
	long int n;
	int fd;

	if ((fd = open(filename,O_RDONLY))==-1){
		perror("open fail");
		exit(EXIT_FAILURE);
	}

	bzero(&buffer,BUFFER);

	n=read(fd,buffer,BUFFER);
	while(n)
	{
		if(n==-1){
			perror("read fails");
			exit(EXIT_FAILURE);
		}
		m=sendto(sockfd,buffer,n,0,(struct sockaddr*)&serv_addr,l);
		if(m==-1){
			perror("send error");
			exit(EXIT_FAILURE);
		}
		count+=m;
		//fprintf(stdout,"----\n%s\n----\n",buffer);
		bzero(buffer,BUFFER);
		n=read(fd,buffer,BUFFER);
	}
}



void handleConnection(int sockfd){
	char buffer[TAM];
	int terminar = 0;
	int m, count;
	int n;
	int conexion;
	int fd;

	const char * cadena;

	while(1) {
		// printf( "Ingrese el mensaje a transmitir: " );
		// memset( buffer, '\0', TAM );
		// fgets( buffer, TAM-1, stdin );

		// n = write( sockfd, buffer, strlen(buffer) );
		// if ( n < 0 ) {
		// 	perror( "escritura de socket" );
		// 	exit( 1 );
		// }

		// Verificando si se escribió: fin
		// buffer[strlen(buffer)-1] = '\0';
		// if( !strcmp( "fin", buffer ) ) {
		// 	terminar = 1;
		// }
		strcpy(buffer, readSock(sockfd));
		printf("Server %s\n", buffer);

		// writeSock(sockfd, buffer);

		switch (atoi(buffer))
		{
		case 1:
			printf("Llego un 1");
			char filename [100] = "20190861730_GOES16-ABI-FD-GEOCOLOR-10848x10848.jpg";
			sendFile(sockfd, filename);
			exit(0);
			break;
		case 2:
			printf("Llego un 2");
			exit(0);
		case 3:
			printf("Llego un 3");
			char cadenita [TAM] = "Id del satélite \n Uptime del satélite \n Versión del software \n Consumo de memoria y CPU";
			writeSock(sockfd, cadenita);
			exit(0);
		default:
			printf("Llego cualquier otra cosa");
			break;
		}

		//preparation of the shipment

		// memset( buffer, '\0', TAM );
		// n = read( sockfd, buffer, TAM );
		// if ( n < 0 ) {
		// 	perror( "lectura de socket" );
		// 	exit( 1 );
		// }
		// printf("%s", buffer);

		// printf( "Respuesta: %s\n", buffer );
		// close(sockfd);
		if( terminar ) {
			printf( "Finalizando ejecución\n" );
			exit(0);
		}
	}
}

void createSockTCP(){
	int sockfd, puerto, n;
	struct hostent *server;
	int terminar = 0;
	char red [100] = "192.168.0.106";

	// if ( argc < 3 ) {
	// 	fprintf( stderr, "Uso %s host puerto\n", argv[0]);
	// 	exit( 0 );
	// }

	puerto = PORT;
	sockfd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( sockfd < 0 ) {
		perror( "ERROR apertura de socket" );
		exit( 1 );
	}

	server = gethostbyname("192.168.0.106");
	if (server == NULL) {
		fprintf( stderr,"Error, no existe el host\n" );
		exit( 0 );
	}
	memset( (char *) &serv_addr, '0', sizeof(serv_addr) );
	serv_addr.sin_family = AF_INET;
	bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length );
	serv_addr.sin_port = htons( puerto );
	if ( connect( sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr ) ) < 0 ) {
		perror( "conexion" );
		exit( 1 );
	}

	handleConnection(sockfd);
}

int main( int argc, char *argv[] ) {
	int sockfd;

	createSockTCP();
	
	return 0;
} 
