#include "server_tcp.h"
#include "header.h"
#include "hash-string.h"
#include "sock_srv_udp.h"

// KEYS
#define HASH    3378490201
#define UFB     75684438
#define SS      2127732462
#define OT      2104739370
#define HELP    1950366504
#define EXIT    2090237503

// COLORS
#define GREEN       "\x1b[32m"
#define RESETCLR    "\x1b[0m"
#define BOLD        "\033[1m"
#define RESETBOLD   "\033[0m"


int createSockTCP2(){
    int sockfd;
	struct sockaddr_in servaddr;
  
    int n, len; 
    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        printf("socket creation failed"); 
        exit(0); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
  
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    if(connect(sockfd, (struct sockaddr*)&servaddr,  
                             sizeof(servaddr)) < 0) { 
        printf("\n Error : Connect Failed \n"); 
    }

    return sockfd;
}

int main() 
{ 
    int sockfd; 
    char buffer[MAXLINE]; 
    char* message = "Hello Server"; 
    struct sockaddr_in servaddr; 
  
    int n, len; 
    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        printf("socket creation failed"); 
        exit(0); 
    }
  
    memset(&servaddr, 0, sizeof(servaddr)); 
  
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
  
    if (connect(sockfd, (struct sockaddr*)&servaddr,  
                             sizeof(servaddr)) < 0) { 
        printf("\n Error : Connect Failed \n"); 
    } 
  
    memset(buffer, 0, sizeof(buffer)); 
    strcpy(buffer, "Hello Server"); 
    write(sockfd, buffer, sizeof(buffer)); 
    printf("Message from server: "); 
    read(sockfd, buffer, sizeof(buffer)); 
    puts(buffer); 
    close(sockfd); 
} 