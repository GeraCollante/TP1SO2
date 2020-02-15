// Client side implementation of UDP client-server model 

#include "header.h"
#include "sock_cli_udp.h"

int firmware;

char * 	cargarInfoSatelite(){
    char buffer [TAM];
	char * ptrBuff;
	memset( buffer, '\0', TAM );
	int strsize = strlen(buffer) + 1;
	// We create dynamic pointer, if not, it gives core errors
	ptrBuff = (char*)malloc(strsize * sizeof(char));
	sprintf(ptrBuff, "id: %sversion: %s \n%s \n%s \n%s \nmem: %s\n", 
    id(),
    version(),
    userTime(),
    sysTime(),
    idleTime(),
    mem());
    // printf("%s", ptrBuff);
    return ptrBuff;
}

char * 	CPU(){
    char buffer [TAM];
	memset( buffer, '\0', TAM );
	char * ptrBuff;
	int strsize = strlen(buffer) + 1;
	// We create dynamic pointer, if not, it gives core errors
	ptrBuff = (char*)malloc(strsize * sizeof(char));
	FILE *fp = fopen("/proc/stat", "r");
	char *ptr;
	ptr = file2Str(fp);
	loadReg2(lreg, ptr);
	int userTime    = atoi(lreg[1])/100;
    int sysTime     = atoi(lreg[2])/100;
	int idleTime    = atoi(lreg[3])/100;
	secondsToDHMS(userTime);
	secondsToDHMS(sysTime);
	secondsToDHMS(idleTime);
    sprintf(ptrBuff, "\n userTime: %s\n sysTime: %s\n idleTime: %s\n", 
    secondsToDHMS(userTime),
    secondsToDHMS(sysTime),
    secondsToDHMS(idleTime)
    );
    // printf("Tam: %lu", strlen(ptrBuff));
	fclose(fp);
    return ptrBuff;
}

int 	crearSocketUDP(){
    /* create UDP socket */
    int udpfd = socket(AF_INET, SOCK_DGRAM, 0); 
    // binding server addr structure to udp sockfd 
    bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
    return udpfd;
}

char * 	id(){
	FILE *fp = fopen("/proc/sys/kernel/hostname", "r");
	char buffer [TAM];
    int n;
	memset( buffer, '\0', TAM );
	char * ptrBuff;
	int strsize = strlen(buffer) + 1;
	// We create dynamic pointer, if not, it gives core errors
	ptrBuff = (char*)malloc(strsize * sizeof(char));
	n = sprintf(ptrBuff, "%s", file2Str2(fp));
	// printf("%s", ptrBuff);
    return ptrBuff;
	fclose(fp);
}

char * 	version(){
	FILE *fp = fopen("/proc/version", "r");
	char buffer [TAM];
	char *version;
    int n;
	memset( buffer, '\0', TAM );
	char * ptrBuff;
	int strsize = strlen(buffer) + 1;
	// We create dynamic pointer, if not, it gives core errors
	ptrBuff = (char*)malloc(strsize * sizeof(char));
	version = file2Str(fp);
	loadReg2(lreg,version);
	sprintf(ptrBuff, "%s",find(lreg, "version"));
    return ptrBuff;
	fclose(fp);
}

char * 	UpTime(){
	FILE *fp = fopen("/proc/uptime", "r");
	char buffer [TAM];
	char * ptrBuff;
    char * str;
    int n, totalSec;
	int t = time(NULL);
	memset( buffer, '\0', TAM );
	int strsize = strlen(buffer) + 1;
	// We create dynamic pointer, if not, it gives core errors
	ptrBuff = (char*)malloc(strsize * sizeof(char));
	str = file2Str(fp);
	loadReg2(lreg,str);
	totalSec = atoi(str);
	time_t raw_time = t - totalSec;
	struct tm * timeinfo;
	timeinfo = localtime (&raw_time);
	strftime (buffer, 80, "%x %X",timeinfo);
    n = sprintf(ptrBuff, "%s", buffer);
    return ptrBuff;
	fclose(fp);
}

char * 	secondsToDHMS(int sec){
	char buffer [TAM];
	memset( buffer, '\0', TAM );
	char * ptrBuff;
	int strsize = strlen(buffer) + 1;
	// We create dynamic pointer, if not, it gives core errors
	ptrBuff = (char*)malloc(strsize * sizeof(char));
    
	int seconds = (sec % 60);
	int minutes = (sec % 3600) / 60;
	int hours = (sec % 86400) / 3600;
	int days = (sec % (86400 * 30)) / 86400;
	sprintf(ptrBuff, "%dD %d:%d:%d", days, hours, minutes, seconds);
    return ptrBuff;
}

char * 	userTime(){
    char buffer [TAM];
	memset( buffer, '\0', TAM );
	char * ptrBuff;
	char * ptr;
	int strsize = strlen(buffer) + 1;
	// We create dynamic pointer, if not, it gives core errors
	ptrBuff = (char*)malloc(strsize * sizeof(char));
	FILE *fp = fopen("/proc/stat", "r");
	ptr = file2Str(fp);
	loadReg2(lreg, ptr);
	int userTime = atoi(lreg[1])/100;
	secondsToDHMS(userTime);
    sprintf(ptrBuff, "userTime: %s", secondsToDHMS(userTime));
    // printf("Tam: %lu", strlen(ptrBuff));
	fclose(fp);
    return ptrBuff;
}

char * 	sysTime(){
    char buffer [TAM];
	memset( buffer, '\0', TAM );
	char * ptrBuff;
	char * ptr;
	int strsize = strlen(buffer) + 1;
	// We create dynamic pointer, if not, it gives core errors
	ptrBuff = (char*)malloc(strsize * sizeof(char));
	FILE *fp = fopen("/proc/stat", "r");
	ptr = file2Str(fp);
	loadReg2(lreg, ptr);
	int sysTime = atoi(lreg[2])/100;
	secondsToDHMS(sysTime);
    sprintf(ptrBuff, "sysTime: %s", secondsToDHMS(sysTime));
    // printf("Tam: %lu", strlen(ptrBuff));
	fclose(fp);
    return ptrBuff;
}

char * 	idleTime(){
    char buffer [TAM];
	memset( buffer, '\0', TAM );
	char * ptrBuff;
	char * ptr;
	int strsize = strlen(buffer) + 1;
	// We create dynamic pointer, if not, it gives core errors
	ptrBuff = (char*)malloc(strsize * sizeof(char));
	FILE *fp = fopen("/proc/stat", "r");
	ptr = file2Str(fp);
	loadReg2(lreg, ptr);
	int idleTime = atoi(lreg[3])/100;
	secondsToDHMS(idleTime);
    sprintf(ptrBuff, "idleTime: %s", secondsToDHMS(idleTime));
    // printf("Tam: %lu", strlen(ptrBuff));
	fclose(fp);
    return ptrBuff;
}

char * 	mem(){
	FILE *fp = fopen("/proc/meminfo", "r");
	char buffer [TAM];
	char * ptrBuff;
	char * str;
	memset( buffer, '\0', TAM );
	int strsize = strlen(buffer) + 1;
	// We create dynamic pointer, if not, it gives core errors
	ptrBuff = (char*)malloc(strsize * sizeof(char));
	str = file2Str(fp);
	loadReg2(lreg, str);
	sprintf(ptrBuff, "%s/%s",find(lreg,"MemFree"),find(lreg,"MemTotal"));
	fclose(fp);
    return ptrBuff;
}