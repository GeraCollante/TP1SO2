#include "sock_cli_tcp.h"
#define h_addr h_addr_list[0] /* for backward compatibility */

void 	recibirArchivo(int newsockfd, char * nombreArchivo){
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
	// sprintf(filename, "%s", nombreArchivo);
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

void 	setFirmware(){
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

void 	showFirmware(){
    int firmAux;
    FILE *fptr;
    if ((fptr = fopen("firmware","rw")) == NULL){
       printf("Error! opening file");
       // Program exits if the file pointer returns NULL.
       exit(1);
    }
	fscanf(fptr, "%i", &firmAux);
	printf("firmware v1.%i\n", firmAux);
}

void 	updateFirmware(){
	int firmAux;
    FILE *fptr;
    if ((fptr = fopen("firmware","rw")) == NULL){
       printf("Error! opening file");
       // Program exits if the file pointer returns NULL.
       exit(1);
    }
	fscanf(fptr, "%i", &firmAux);
	// printf("Old firmware: %i\n", firmAux);
	firmware = firmAux + 1;
	// printf("New firmware: %i\n", firmware);
    fclose(fptr);
	if ((fptr = fopen("firmware","w")) == NULL){
       printf("Error! opening file");
       // Program exits if the file pointer returns NULL.
       exit(1);
    }
	fprintf(fptr, "%i", firmware);
	fclose(fptr);
}

void 	manejarConexionTCP(int sockfd, char n){
    // printf("N vale: %c\n", n);
    switch(n)
    {
    case '1':
        puts("Recibiendo archivo cliente");

        // memset(buffer, 0, sizeof(buffer));
        // read(sockfd, buffer, sizeof(buffer));
        // puts(buffer);
        // setFirmware(atoi(buffer));
        updateFirmware();
        recibirArchivo(sockfd, "moshisha");
        showFirmware();
        // system("reboot");
        break;
    case '2':
        puts("Enviando archivo img");
        enviarArchivo(sockfd, "20190861730_GOES16-ABI-FD-GEOCOLOR-10848x10848.jpg");
        break;
    default:
        break;
    }
}

int 	crearListenTCP(){
	int listenfd;
    void sig_chld(int); 
  
    /* create listening TCP socket */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 

    listen(listenfd, 10); 

	return listenfd;
}

void 	enviarArchivo(int sockfd, char * filename){	
	char buffer[BUFFER];
	int l=sizeof(struct sockaddr_in);
    off_t count=0, m;
	// ,sz;//long
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
		m=sendto(sockfd,buffer,n,0,(struct sockaddr*)&cliaddr,l);
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