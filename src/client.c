#include "client_tcp.h"
#include "sock_cli_udp.h"
#include "header.h"
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

struct sockaddr_in clienteaddress, serveraddress;

int max(int x, int y) 
{
    int max = (x>y) ? x : y;
    return max;
}

int createSocketTCP(){
    int listenfd; 

    /* create listening TCP socket */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&clienteaddress, sizeof(clienteaddress));
    clienteaddress.sin_family = AF_INET; 
    clienteaddress.sin_addr.s_addr = htonl(INADDR_ANY);
    clienteaddress.sin_port = htons(PORT); 

	// char buffer[INET_ADDRSTRLEN];
	// inet_ntop( AF_INET, &clienteaddress.sin_addr, buffer, sizeof( buffer ));
	// printf( "address:%s\n", buffer );

    // binding server addr structure to listenfd 
    bind(listenfd, (struct sockaddr*)&clienteaddress, sizeof(clienteaddress));

    listen(listenfd, 10); 
    return listenfd;
}


int createSocketUDP(){
    /* create UDP socket */
    int udpfd;
    udpfd = socket(AF_INET, SOCK_DGRAM, 0); 
    // binding server addr structure to udp sockfd 
    bind(udpfd, (struct sockaddr*)&clienteaddress, sizeof(clienteaddress)); 
    return udpfd;
}

void handleConnection2(int listenfd, int udpfd){
    int connfd, nready, maxfdp1; 
    char buffer[MAXLINE]; 
    pid_t childpid; 
    fd_set rset; 
    ssize_t n; 
    socklen_t len; 
    const int on = 1;  
    char* message = "Hello Client"; 
    void sig_chld(int); 

    // clear the descriptor set 
    FD_ZERO(&rset);
  
    // get maxfd 
    maxfdp1 = max(listenfd, udpfd) + 1; 
    for (;;) { 
  
        // set listenfd and udpfd in readset 
        FD_SET(listenfd, &rset); 
        FD_SET(udpfd, &rset); 
  
        // select the ready descriptor 
        nready = select(maxfdp1, &rset, NULL, NULL, NULL); 
  
        // if tcp socket is readable then handle 
        // it by accepting the connection 
        if (FD_ISSET(listenfd, &rset)) { 
            len = sizeof(serveraddress); 
            connfd = accept(listenfd, (struct sockaddr*)&serveraddress, &len); 
            if ((childpid = fork()) == 0) { 
                close(listenfd); 
                bzero(buffer, sizeof(buffer));
                printf("Message From TCP client: ");
                read(connfd, buffer, sizeof(buffer));
                puts(buffer);

                printf("Que onda: %s", buffer);
                readSockTCP(connfd); 
                write(connfd, (const char*)message, sizeof(buffer)); 
                writeSockTCP(connfd, "Moshisha");

                close(connfd); 
                exit(0); 
            } 
            close(connfd); 
        } 
        // if udp socket is readable receive the message. 
        if (FD_ISSET(udpfd, &rset)) { 
            len = sizeof(serveraddress); 
            bzero(buffer, sizeof(buffer)); 
            // printf("\nMessage from UDP client: "); 
            n = recvfrom(udpfd, buffer, sizeof(buffer), 0, 
                         (struct sockaddr*)&serveraddress, &len);
            puts(buffer); 
            sendto(udpfd, (const char*)message, sizeof(buffer), 0, 
                   (struct sockaddr*)&serveraddress, sizeof(serveraddress)); 
        } 
    } 
}

int main( int argc, char *argv[] ){
	int listenfd, connfd, udpfd, nready, maxfdp1; 
    char buffer[MAXLINE]; 
    pid_t childpid; 
    fd_set rset; 
    ssize_t n; 
    socklen_t len; 
    const int on = 1; 
    struct sockaddr_in cliaddr, servaddr; 
    char* message = "Hello Client"; 
    void sig_chld(int); 
  
    /* create listening TCP socket */
    listenfd = socket(AF_INET, SOCK_STREAM, 0); 
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // binding server addr structure to listenfd 
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
    listen(listenfd, 10); 
  
    /* create UDP socket */
    udpfd = socket(AF_INET, SOCK_DGRAM, 0); 
    // binding server addr structure to udp sockfd 
    bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
  
    // clear the descriptor set 
    FD_ZERO(&rset); 
  
    // get maxfd 
    maxfdp1 = max(listenfd, udpfd) + 1; 
    for (;;) { 
  
        // set listenfd and udpfd in readset 
        FD_SET(listenfd, &rset); 
        FD_SET(udpfd, &rset); 
  
        // select the ready descriptor 
        nready = select(maxfdp1, &rset, NULL, NULL, NULL); 
  
        // if tcp socket is readable then handle 
        // it by accepting the connection 
        if (FD_ISSET(listenfd, &rset)) { 
            len = sizeof(cliaddr); 
            connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len); 
            if ((childpid = fork()) == 0) { 
                close(listenfd); 
                bzero(buffer, sizeof(buffer)); 
                printf("Message From TCP client: "); 
                read(connfd, buffer, sizeof(buffer)); 
                puts(buffer); 
                write(connfd, (const char*)message, sizeof(buffer)); 
                close(connfd); 
                exit(0); 
            } 
            close(connfd); 
        } 
        // if udp socket is readable receive the message. 
        if (FD_ISSET(udpfd, &rset)) { 
            len = sizeof(cliaddr); 
            bzero(buffer, sizeof(buffer)); 
            printf("\nMessage from UDP client: "); 
            n = recvfrom(udpfd, buffer, sizeof(buffer), 0, 
                         (struct sockaddr*)&cliaddr, &len); 
            puts(buffer); 
            sendto(udpfd, (const char*)message, sizeof(buffer), 0, 
                   (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
        } 
    } 
}