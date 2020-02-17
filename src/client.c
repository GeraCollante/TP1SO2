/**
 * @file client.c
 * @author Gerardo Collante
 * @brief 
 * @version 0.1
 * @date 2020-02-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "sock_cli_udp.h"
#include "sock_cli_tcp.h"

#define BUFFSIZE 256

/**
 * @brief Handler simultaneo de conexiones TPC y UDP
 * 
 * @param listenfd 
 * @param udpfd 
 */
void waitTCPUDP(int listenfd, int udpfd){
    int connfd, maxfdp1; 
    char buffer[MAXLINE];
    pid_t childpid; 
    fd_set rset;
    socklen_t len;
    void sig_chld(int);

    FD_ZERO(&rset); 
  
    maxfdp1 = max(listenfd, udpfd) + 1; 

    for (;;) {
        //Set listenfd and udpfd in readset 
        FD_SET(listenfd, &rset); 
        FD_SET(udpfd, &rset); 
  
        // Select the ready descriptor
        select(maxfdp1, &rset, NULL, NULL, NULL); 
  
        // if tcp socket is readable then handle it by accepting the connection
        if (FD_ISSET(listenfd, &rset)) { 
            len = sizeof(cliaddr); 
            connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len); 
            if ((childpid = fork()) == 0) { 
                close(listenfd); 
                bzero(buffer, sizeof(buffer));
                read(connfd, buffer, sizeof(buffer));
				manejarConexionTCP(connfd, buffer[0]);
                close(connfd); 
                exit(0); 
            } 
            close(connfd); 
        } 
        // if udp socket is readable receive the message. 
        if (FD_ISSET(udpfd, &rset)) {
            len = sizeof(cliaddr); 
            bzero(buffer, sizeof(buffer));
            recvfrom(udpfd, buffer, sizeof(buffer), 0, 
                         (struct sockaddr*)&cliaddr, &len);

            // Enviar información
            showCpuinfo(udpfd);
            showVersion(udpfd);
            showUptime(udpfd);
            showStats(udpfd);
            showMeminfo(udpfd);
        } 
    } 
}

/**
 * @brief Creación de cliente
 * 
 */
void cliente(){
    printf("%s\n", "Cliente satelite");
    showFirmware();
    int listenfd, udpfd;
    void sig_chld(int); 
  
	listenfd = crearListenTCP();
    udpfd    = crearSocketUDP();

	waitTCPUDP(listenfd, udpfd);
}

int main() 
{ 
    cliente();
}