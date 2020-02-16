// Server side implementation of UDP client-server model 
#include "sock_srv_udp.h"

int     crearSocketUDP(){
	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        printf("socket creation failed"); 
        exit(0); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
  
    // Filling server information 
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("169.254.237.70");

	return sockfd;
}