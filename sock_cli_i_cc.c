#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#define TAM 256
#define PORT 10000

void handleConnection(int sockfd){
	char buffer[TAM];
	int terminar = 0;
	int n;

	while(1) {
		printf( "Ingrese el mensaje a transmitir: " );
		memset( buffer, '\0', TAM );
		fgets( buffer, TAM-1, stdin );

		n = write( sockfd, buffer, strlen(buffer) );
		if ( n < 0 ) {
			perror( "escritura de socket" );
			exit( 1 );
		}

		// Verificando si se escribió: fin
		buffer[strlen(buffer)-1] = '\0';
		if( !strcmp( "fin", buffer ) ) {
			terminar = 1;
		}

		memset( buffer, '\0', TAM );
		n = read( sockfd, buffer, TAM );
		if ( n < 0 ) {
			perror( "lectura de socket" );
			exit( 1 );
		}
		printf( "Respuesta: %s\n", buffer );
		if( terminar ) {
			printf( "Finalizando ejecución\n" );
			exit(0);
		}
	}
}

void createSockTCP(){
	int sockfd, puerto, n;
	struct sockaddr_in serv_addr;
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
