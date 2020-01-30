#include "client_tcp.h"
#include "header.h"

// int main( int argc, char *argv[] ) {

// 	// setFirmware();
// 	createSockTCP();
	
// 	return 0;
// } 

void setFirmware(){
	int firmAux;
    FILE *fptr;
    if ((fptr = fopen("firmware","rw")) == NULL){
       printf("Error! opening file");
       // Program exits if the file pointer returns NULL.
       exit(1);
    }
	fscanf(fptr, "%i", &firmAux);
	firmware = firmAux;
	printf("version: %i\n", firmware);
	fclose(fptr);
}

/**
 * @brief Write to the socket
 * 
 * @param sockfd 
 * @param str 
 */
void writeSock(int sockfd, char * str)
{
	int n;
	char buffer [TAM];
	memset( buffer, '\0', TAM );
	strcpy(buffer, str);
	printf("%s", buffer);
	n = write( sockfd, buffer, strlen(buffer) );
	if ( n < 0 ){
		perror( "socket write" );
		exit(1);
	}
}

/**
 * @brief Read socket
 * 
 * @param sockfd 
 * @return char* 
 */
char * readSock(int sockfd)
{
	int n;
	char buffer [TAM];
	memset( buffer, '\0', TAM );
	char * ptrBuff;
	int keylen = strlen(buffer) + 1;
	// We create dynamic pointer, if not, it gives core errors
	ptrBuff = (char*)malloc(keylen * sizeof(char));
	n = read( sockfd, buffer, TAM);
	if ( n < 0 ) {
		perror( "lectura de socket" );
		exit(1);
	}
	strcpy(ptrBuff, buffer);
	printf("%s", ptrBuff);
    return ptrBuff;
}

void recFile(int newsockfd){
	//Processing the file name with the date
	char buffer[BUFFER],filename[256];
	time_t intps;
	long int n, m,count=0;
	struct tm* tmi;
	int fd;
	
	//Processing the file name with the date
	bzero(filename,256);
	intps = time(NULL);
	tmi = localtime(&intps);
	bzero(filename,256);
	sprintf(filename, "%s", "codigo.c");
	// sprintf(filename,"clt.%d.%d.%d.%d.%d.%d",tmi->tm_mday,tmi->tm_mon+1,1900+tmi->tm_year,tmi->tm_hour,tmi->tm_min,tmi->tm_sec);
	printf("Creating the copied output file : %s\n",filename);
	
	if ((fd=open(filename,O_CREAT|O_WRONLY,0600))==-1)
	{
		perror("open fail");
		exit (3);
	}
	
	bzero(buffer,BUFFER);

	clock_t begin = clock();
	
	n=recv(newsockfd,buffer, BUFFER,0);

	while(n) {
		if(n==-1){
			perror("recv fail");
			exit(5);
		}
		if((m=write(fd,buffer,n))==-1){
			perror("write fail");
			exit (6);
		}
		count=count+m;
		bzero(buffer,BUFFER);
		n=recv(newsockfd,buffer,BUFFER,0);
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time rec file: %f sec\n", time_spent);
	close(fd);
}

/**
 * @brief Send file
 * 
 * @param sockfd 
 * @param filename 
 */

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
	// clock_t begin = clock();

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
		// fprintf(stdout,"----\n%s\n----\n",buffer);
		bzero(buffer,BUFFER);
		n=read(fd,buffer,BUFFER);
	}
	// clock_t end = clock();
	// double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	// printf("Time send file: %f sec\n", time_spent);
}


/**
 * @brief Handle the connection between client and server
 * 
 * @param sockfd 
 */
void handleConnection(int sockfd){
	char buffer[TAM];
	int terminar = 0;
	int m, count;
	int n;
	int conexion;
	int fd;

	while(1) {
		// printf( "Ingrese el mensaje a transmitir: " );
		// memset( buffer, '\0', TAM );
		// fgets( buffer, TAM-1, stdin );


		// Verificando si se escribió: fin
		// buffer[strlen(buffer)-1] = '\0';
		// if( !strcmp( "fin", buffer ) ) {
		// 	terminar = 1;
		// }
		strcpy(buffer, readSock(sockfd));
		printf("Server %s\n", buffer);

		switch (atoi(buffer))
		{
		case 2:
			printf("Sending Scan to Earth Station");
			char filename [100] = "20190861730_GOES16-ABI-FD-GEOCOLOR-10848x10848.jpg";
			sendFile(sockfd, filename);
			exit(0);
			break;
		case 1:
			printf("Llego un 2");
			recFile(sockfd);
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

/**
 * @brief A TCP socket is created
 * 
 */
void createSockTCP(){
	int sockfd, puerto, n;
	struct hostent *server;
	int terminar = 0;
	char red [100] = "192.168.0.106";

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