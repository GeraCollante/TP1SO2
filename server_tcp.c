#include "header.h"
#include "server_tcp.h"

int main( int argc, char *argv[] ) {
	
	updateFirmware();
	createSocketTCP();
	
	return 0; 
}

void updateFirmware(){
    // firmware = 1;
	int firmAux;
    FILE *fptr;
    if ((fptr = fopen("firmware","rw")) == NULL){
       printf("Error! opening file");
       // Program exits if the file pointer returns NULL.
       exit(1);
    }
	fscanf(fptr, "%i", &firmAux);
	printf("Old firmware: %i\n", firmAux);
	firmware = firmAux + 1;
	printf("New firmware: %i\n", firmware);
    fclose(fptr);
	if ((fptr = fopen("firmware","w")) == NULL){
       printf("Error! opening file");
       // Program exits if the file pointer returns NULL.
       exit(1);
    }
	fprintf(fptr, "%i", firmware);
	fclose(fptr);
}

/**
 * @brief 
 * 
 * @param sockfd 
 * @param cadena 
 */
void writeSock(int sockfd, char * cadena)
{
	int n;
	char buffer [TAM];
	printf("Entre acá\n");
	strcpy(buffer, cadena);
	printf("%s", buffer);
	n = write( sockfd, buffer, strlen(buffer) );
	if ( n < 0 ) {
		perror( "escritura de socket" );
		exit( 1 );
	}
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
	sprintf(filename,"clt.%d.%d.%d.%d.%d.%d",tmi->tm_mday,tmi->tm_mon+1,1900+tmi->tm_year,tmi->tm_hour,tmi->tm_min,tmi->tm_sec);
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

char * readSock(int sockfd)
{
	int n;
	char buffer [TAM];
	char * ptrBuff;
	int keylen = strlen(buffer) + 1;
	// Copy password into dynamically allocated storage
	ptrBuff = (char*)malloc(keylen * sizeof(char));
	printf("Entre aca");
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

void handleConnection(int newsockfd){
	int n;
	char buffer [TAM];
	char filename [100] = "sock_cli_i_cc.c";

	while (1) {
				// memset( buffer, 0, TAM );
				printf( "Ingrese el mensaje a transmitir: " );
				memset( buffer, '\0', TAM );
				fgets( buffer, TAM-1, stdin );

				writeSock(newsockfd, buffer);

				printf("strcmp: %i", strcmp(buffer,"3"));
				printf("sss %s sss", buffer);
				printf("num es: %i", atoi(buffer));

				switch (atoi(buffer))
				{
				case 1:
					sendFile(newsockfd, filename);
					break;
				case 2:
					recFile(newsockfd);
					break;
				//Imprimir parametros
				case 3:
					memset(buffer, '\0', TAM );
					strcpy(buffer, readSock(newsockfd));
					printf("Buffer es: %s", buffer);
					break;
				default:
					break;
				}

				// n = read( newsockfd, buffer, TAM-1 );
				// if ( n < 0 ) {
				// 	perror( "lectura de socket" );
				// 	exit(1);
				// }

				// n = write( newsockfd, "1", 18 );
				// if ( n < 0 ) {
				// 	perror( "escritura en socket" );
				// 	exit( 1 );
				// }

				// strcpy(buffer, readSock(newsockfd));

				// writeSock(newsockfd, "Mbappe");

				// if (strcmp(buffer,"Messi")==0)
				// {
				// 	printf("Dormimos");
				// 	sleep(5);
				// 	exit(1);
				// }
				
				// printf("Cliente %s\n", buffer);

				// switch (atoi(buffer))
				// {
				// case 1:
				// 	printf("Llego un 1");
				// 	exit(0);
				// 	break;
				// case 2:
				// 	printf("Llego un 2");
				// 	exit(0);
				// case 3:
				// 	printf("Llego un 3");
				// 	exit(0);
				// default:
				// 	printf("Llego cualquier otra cosa");
				// 	break;
				// }				

				// n = read( newsockfd, buffer, TAM-1 );
				// if ( n < 0 ) {
				// 	perror( "lectura de socket" );
				// 	exit(1);
				// }

				printf( "PROCESO %d. ", getpid() );
				// printf( "Recibí: %s", buffer );
						
				// n = write( newsockfd, "Obtuve su mensaje", 18 );
				// if ( n < 0 ) {
				// 	perror( "escritura en socket" );
				// 	exit( 1 );
				// }
				// Verificación de si hay que terminar
				buffer[strlen(buffer)-1] = '\0';
				if( !strcmp( "fin", buffer ) ) {
					printf( "PROCESO %d. Como recibí 'fin', termino la ejecución.\n\n", getpid() );
					exit(0);
				}
			}
}


void createSocketTCP(){
	int sockfd, newsockfd, puerto, clilen, pid;
	struct sockaddr_in cli_addr;
	int n;

	// if ( argc < 2 ) {
    //     	fprintf( stderr, "Uso: %s <puerto>\n", argv[0] );
	// 	exit( 1 );
	// }

	sockfd = socket( AF_INET, SOCK_STREAM, 0);
	if ( sockfd < 0 ) { 
		perror( " apertura de socket ");
		exit( 1 );
	}

	memset( (char *) &serv_addr, 0, sizeof(serv_addr) );
	puerto = PORT;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons( puerto );

	if ( bind(sockfd, ( struct sockaddr *) &serv_addr, sizeof( serv_addr ) ) < 0 ) {
		perror( "ligadura" );
		exit( 1 );
	}

	printf( "Proceso: %d - socket disponible: %d\n", getpid(), ntohs(serv_addr.sin_port) );

	listen( sockfd, 5 );
	clilen = sizeof( cli_addr );

	while( 1 ) {
		newsockfd = accept( sockfd, (struct sockaddr *) &cli_addr, &clilen );
		if ( newsockfd < 0 ) {
			perror( "accept" );
			exit( 1 );
		}

		pid = fork(); 
		if ( pid < 0 ) {
			perror( "fork" );
			exit( 1 );
		}

		if ( pid == 0 ) {  // Proceso hijo
			close( sockfd );
			handleConnection(newsockfd);
		}
		else {
			printf( "SERVIDOR: Nuevo cliente, que atiende el proceso hijo: %d\n", pid );
			close( newsockfd );
		}
	}
}