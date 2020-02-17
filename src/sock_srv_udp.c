// Server side implementation of UDP client-server model 
#include "sock_srv_udp.h"

/**
 * @brief Leer mensaje UDP
 * 
 * @param sockfd 
 */
void readUDP(int sockfd){
	char buffer[MAXLINE];
	socklen_t server_addr_len;
	// printf("Información recibida: \n");
	memset(buffer, '\0', MAXLINE);
	recvfrom(sockfd, (char*)buffer, MAXLINE, 
	0, (struct sockaddr*)&servaddr, 
	&server_addr_len); 
	printf("%s", buffer);
}

/**
 * @brief Creación socket UDP
 * 
 * @param port 
 * @param ipaddr 
 * @return sockfd
 */
int crearSocketUDP(int port, char* ipaddr){
    int l;
	int sfd;
    
	sfd = socket(AF_INET,SOCK_DGRAM,0);
	if (sfd == -1){
        perror("socket fail");
        return EXIT_FAILURE;
	}
    
    // preparation of the destination socket address
	l=sizeof(struct sockaddr_in);
	bzero(&servaddr,l);
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(port);
    if (inet_pton(AF_INET,ipaddr,&servaddr.sin_addr)==0){
		printf("Invalid IP adress\n");
		return EXIT_FAILURE;
	}
    
    return sfd;
}

// int     crearSocketUDP(){
// 	int sockfd;
// 	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
//         printf("socket creation failed"); 
//         exit(0); 
//     } 
  
//     memset(&servaddr, 0, sizeof(servaddr)); 
  
//     // Filling server information 
//     servaddr.sin_family = AF_INET;
//     servaddr.sin_port = htons(PORT);
//     servaddr.sin_addr.s_addr = inet_addr("169.254.237.70");

// 	return sockfd;
// }