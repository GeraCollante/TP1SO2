#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/if_link.h>

const char * getIP(){
    int TAM = 256;
    struct ifaddrs *ifaddr, *ifa;
    int family, s, n;
    char host[NI_MAXHOST];
    char * net = "enp3s0";
	char * ptrBuff;
	int keylen = strlen(host) + 1;
	ptrBuff = (char*)malloc(keylen * sizeof(char));
	memset( host, '\0', TAM );

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    /* Walk through linked list, maintaining head pointer so we
        can free list later */

    for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
        if (ifa->ifa_addr == NULL)
            continue;

        family = ifa->ifa_addr->sa_family;

        /* Display interface name and family (including symbolic
            form of the latter for the common families) */

        char * netname= ifa->ifa_name;
        if(strcmp(netname, net)==0){
            
            if (family == AF_INET) {
                s = getnameinfo(ifa->ifa_addr,
                        (family == AF_INET) ? sizeof(struct sockaddr_in) :
                                                sizeof(struct sockaddr_in6),
                        host, NI_MAXHOST,
                        NULL, 0, NI_NUMERICHOST);
                if (s != 0) {
                    printf("getnameinfo() failed: %s\n", gai_strerror(s));
                    exit(EXIT_FAILURE);
                }
                strcpy(ptrBuff, host);
            }
        }
    }
    freeifaddrs(ifaddr);
    return ptrBuff;
}

int main(int argc, char *argv[])
{
    printf("IP: %s",getIP());
    exit(EXIT_SUCCESS);
}