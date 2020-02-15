// Client program 

#include "sock_cli_udp.h"
#include "sock_cli_tcp.h"

void waitTCPUDP(int listenfd, int udpfd){
    int connfd, nready, maxfdp1; 
    char buffer[MAXLINE]; 
    char michaelBuffer[MAXLINE];
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
            len = sizeof(cliaddr); 
            connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len); 
            if ((childpid = fork()) == 0) { 
                close(listenfd); 
                bzero(buffer, sizeof(buffer)); 
                // printf("Message From TCP client: ");
                read(connfd, buffer, sizeof(buffer));
				manejarConexionTCP(connfd, buffer[0]);
                // bzero(buffer, sizeof(buffer)); 
                // printf("Message From TCP client: "); 
                // read(connfd, buffer, sizeof(buffer)); 
                // puts(buffer); 
                // write(connfd, (const char*)message, sizeof(buffer)); 
				// recibirArchivo(connfd);
                close(connfd); 
                exit(0); 
            } 
            close(connfd); 
        } 
        // if udp socket is readable receive the message. 
        if (FD_ISSET(udpfd, &rset)) {
            strcpy(michaelBuffer, cargarInfoSatelite());
            printf("%s", michaelBuffer);
            len = sizeof(cliaddr); 
            bzero(buffer, sizeof(buffer));
            n = recvfrom(udpfd, buffer, sizeof(buffer), 0, 
                         (struct sockaddr*)&cliaddr, &len);
            // puts(buffer);
            sendto(udpfd, (const char*)michaelBuffer, sizeof(buffer), 0, 
                   (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
            printf("Información enviada.\n");
            // bzero(michaelBuffer, sizeof(michaelBuffer)); 
        } 
    } 
}

int main() 
{ 
    int listenfd, udpfd;
    void sig_chld(int); 
  
	listenfd = crearListenTCP();
    udpfd    = crearSocketUDP();

    showFirmware();
	waitTCPUDP(listenfd, udpfd);
}