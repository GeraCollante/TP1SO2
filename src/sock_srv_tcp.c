#include "header.h"
#include "sock_srv_tcp.h"
#include "hash-string.h"

// PASS
#define HASH 	3378490201

// COLORS
#define GREEN       "\x1b[32m"
#define RESETCLR    "\x1b[0m"
#define BOLD        "\033[1m"
#define RESETBOLD   "\033[0m"

/**
 * @brief Verificación de ingreso correcto.
 * 
 * @return int Condición de ingreso.
 */
int 	logSuccess(){
    int attemps = 0;
    do
    {
        if(
            login()==1
            // 1
            )
        {
            printf(GREEN "Succesful login.\n");
			return 1;
            // server();
            // menu();
            // exit(EXIT_SUCCESS);
        }
        else
        {
            attemps += 1;
            printf("Failed login. Remaining attempts: %i.", ATTEMPS - attemps);
        }
    }while(attemps<3);
    return 0;
}

/**
 * @brief Para retrocompatibilidad
 * 
 * @param stream 
 * @return int 
 */
int 	fileno(FILE *stream);

/**
 * @brief Menu de login
 * 
 * @return int Ingreso correcto.
 */
int 	login(){
    struct termios oflags, nflags;
    char    username[256];
    char    password[128];
    int     login = 0;

    printf("Ingress username: ");
    fgets(username, sizeof(username), stdin);
    username[strlen(username) - 1] = 0;

    tcgetattr(fileno(stdin), &oflags);  // Get old terminal settings
    nflags = oflags;                    // Save old terminal in new terminal
    nflags.c_lflag &= ~ECHO;            // Desactive echo flags
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSADRAIN, &nflags) != 0) // Set new terminal
    {
        perror("tcsetattr");
        return -1;
    }

    printf("Ingress password: ");
    fgets(password, sizeof(password), stdin);
    password[strlen(password) - 1] = 0;
    // printf("Entered username        : %s\n", username);
    // printf("Entered password        : %s\n", password);
    strcat(username, password);                             //Created userpass
    // printf("Hash is: %u",string_hash(username));
    login = string_hash(username) == HASH ? 1 : 0;
    // login == 1 ? printf("Contraseña correcta") : printf("Contraseña incorrecta");

    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)    // Active old terminal
    { 
        perror("tcsetattr");
        return -1;
    }

    return login;
}

/**
 * @brief Creación de hash
 * 
 * @param string cadena para el hash
 * @return hash
 */
unsigned int string_hash(void *string){
	/* This is the djb2 string hash function */

	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}

	return result;
}

/**
 * @brief Enviar archivo via TCP
 * 
 * @param sockfd 
 * @param filename 
 */
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
		m=sendto(sockfd,buffer,n,0,(struct sockaddr*)&servaddr,l);
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
 * @brief Recibir archivo via TCP
 * 
 * @param newsockfd 
 * @param nombreArchivo 
 */
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

/**
 * @brief Inicia actualización de firmware
 * 
 * @param sockfd 
 */
void 	actualizarFirmware(int sockfd){
	char buffer[MAXLINE];
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, "2");
    write(sockfd, buffer, sizeof(buffer));
	manejarConexionTCP(sockfd, atoi(buffer));
}

/**
 * @brief Solicita envio de imagen
 * 
 * @param sockfd 
 */
void 	startScanning(int sockfd){
	char buffer[MAXLINE];
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, "1");
    write(sockfd, buffer, sizeof(buffer));
	// Enviar archivo
	manejarConexionTCP(sockfd, atoi(buffer));
}

/**
 * @brief Creacion de socket TCP
 * 
 * @return int 
 */
int 	crearSocketTCP(){
    int sockfd;

    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        printf("socket creation failed"); 
        exit(0); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
  
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr("169.254.237.70"); 
    // servaddr.sin_addr.s_addr = inet_addr("192.168.0.31");
  
    if (connect(sockfd, (struct sockaddr*)&servaddr,  
                             sizeof(servaddr)) < 0) { 
        printf("\n Error : Connect Failed \n"); 
    } 

	return sockfd;
}

/**
 * @brief Handler conexion TCP
 * 
 * @param sockfd 
 * @param n 
 */
void 	manejarConexionTCP(int sockfd, int n){
    switch(n)
    {
    case 1:
		puts("Enviando archivo cliente");

		// memset(buffer, 0, sizeof(buffer));
    	// strcpy(buffer, "u");
    	// write(sockfd, buffer, sizeof(buffer));

        enviarArchivo(sockfd, "bin/client");
        break;
    case 2:
		puts("Recibiendo archivo img");
        recibirArchivo(sockfd, "client");
        break;
    default:
        break;
    }
}