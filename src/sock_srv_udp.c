// Server side implementation of UDP client-server model 

#include "sock_srv_udp.h"
  
struct sockaddr_in servaddr, cliaddr;

void handleUDP(){
    int sockfd;
    sockfd = createSockUDP();
    recInfo(sockfd);
}

int createSockUDP(){
    int sockfd;
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 

    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family         = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr    = INADDR_ANY; 
    servaddr.sin_port           = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    return sockfd;
}

void recInfo(int sockfd){
    char buffer[MAXLINE]; 
    int len, n; 
    len = sizeof(cliaddr);  //len is value/resuslt 
  
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len); 
    buffer[n] = '\0';
    printf("Client: %s", buffer);
}
