// Client side implementation of UDP client-server model 

#include "header.h"
#include "sock_cli_udp.h"

int firmware;

// char * 	cargarInfoSatelite(){
//     char buffer [TAM];
// 	char * ptrBuff;
// 	memset( buffer, '\0', TAM );
// 	int strsize = strlen(buffer) + 1;
// 	// We create dynamic pointer, if not, it gives core errors
// 	ptrBuff = (char*)malloc(strsize * sizeof(char));
// 	sprintf(ptrBuff, "id: %sversion: %s \n%s \n%s \n%s \nmem: %s\n", 
//     id(),
//     version(),
//     userTime(),
//     sysTime(),
//     idleTime(),
//     mem());
//     // printf("%s", ptrBuff);
//     return ptrBuff;
// }

// char * 	CPU(){
//     char buffer [TAM];
// 	memset( buffer, '\0', TAM );
// 	char * ptrBuff;
// 	int strsize = strlen(buffer) + 1;
// 	// We create dynamic pointer, if not, it gives core errors
// 	ptrBuff = (char*)malloc(strsize * sizeof(char));
// 	FILE *fp = fopen("/proc/stat", "r");
// 	char *ptr;
// 	ptr = file2Str(fp);
// 	loadReg2(lreg, ptr);
// 	int userTime    = atoi(lreg[1])/100;
//     int sysTime     = atoi(lreg[2])/100;
// 	int idleTime    = atoi(lreg[3])/100;
// 	secondsToDHMS(userTime);
// 	secondsToDHMS(sysTime);
// 	secondsToDHMS(idleTime);
//     sprintf(ptrBuff, "\n userTime: %s\n sysTime: %s\n idleTime: %s\n", 
//     secondsToDHMS(userTime),
//     secondsToDHMS(sysTime),
//     secondsToDHMS(idleTime)
//     );
//     // printf("Tam: %lu", strlen(ptrBuff));
// 	fclose(fp);
//     return ptrBuff;
// }

int 	crearSocketUDP(){
    /* create UDP socket */
    int udpfd = socket(AF_INET, SOCK_DGRAM, 0); 
    // binding server addr structure to udp sockfd 
    bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
    return udpfd;
}


/**
* /proc/cpuinfo
* This  is  a collection of CPU and system architecture dependent items, for each supported architecture a different list.
* Two common entries are processor which gives CPU number and bogomips; a system constant that is calculated during kernel
* initialization.  SMP  machines  have  information  for each CPU.
*/
void showCpuinfo(int udpfd){
    FILE *fd;

	char cpuinfo1[BUFFSIZE+1];
	char cpuinfo2[BUFFSIZE+1];
	char str1 [20];
	char str2 [20];
	char str3 [20];
	char str4 [20];
	char str5 [20];
	char str6 [20];

	fd = fopen("/proc/cpuinfo","r");
	fgets(cpuinfo1, BUFFSIZE+1, fd);
	fgets(cpuinfo1, BUFFSIZE+1, fd);
	fgets(cpuinfo2, BUFFSIZE+1, fd);
	fgets(cpuinfo2, BUFFSIZE+1, fd);
	fgets(cpuinfo2, BUFFSIZE+1, fd);
	fclose(fd);
	fflush(fd);

    //Filtra Type y lo imprime
    // sscanf(cpuinfo1,"%*s %*s %s ", str1);
    // printf("Type: %s \n",str1);

    //Filtra el modelo, lo copia a str2 y la imprime
    sscanf(cpuinfo2,"%*s %*s %*s %s %s %s %s %s %s", str1, str2, str3, str4, str5, str6);
    printf("Model: %s %s %s %s %s\n",str1, str2, str3, str5, str6);
    char buffer[MAXLINE];
    bzero(buffer, sizeof(buffer));
    sprintf(buffer, "Model: %s %s %s %s %s\n",str1, str2, str3, str5, str6);
    sendto(udpfd, (const char*)buffer, sizeof(buffer), 0, 
           (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
    // printf("Información enviada.\n");
}

/**
* /proc/version
* This string identifies the kernel version that is currently running.
* It includes the contents of /proc/sys/kernel/ostype, /proc/sys/kernel/osrelease
* and /proc/sys/kernel/version.  For example:
* Linux version 1.0.9 (quinlan@phaze) #1 Sat May 14 01:51:54 EDT 1994
*/
void showVersion(int udpfd){
    FILE *fd;
    char version[BUFFSIZE+1];
    char str1 [20];

    fd = fopen("/proc/version","r");
	fgets(version, BUFFSIZE+1, fd);
	fclose(fd);
	fflush(fd);

    //Filtra Version y la imprime
	sscanf(version,"%*s %*s %s ", str1);
	printf("Kernel Version: %s \n",str1);

    char buffer[MAXLINE];
    bzero(buffer, sizeof(buffer));
    sprintf(buffer, "Kernel Version: %s \n",str1);
    sendto(udpfd, (const char*)buffer, sizeof(buffer), 0, 
           (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
    // printf("Información enviada.\n");
}

/**
* /proc/uptime
* This file contains two numbers: the uptime of the system (seconds),
* and the amount of time spent in idle process (seconds).
*/
int showUptime(int udpfd){
    FILE *fd;
	int time=0, days=0, hours=0, mins=0, secs=0;

	fd = fopen("/proc/uptime", "r");
	fscanf(fd,"%d",&time);

	days = time / 86400;
	time = time % 86400;
	hours  = time / 3600;
	time = time % 3600;
	mins = time / 60;
	secs = time % 60;

	fclose(fd);
	fflush(fd);

	//Filtra uptime y lo imprime
	printf("Uptime: %dd:%dh:%dm:%ds\n",days,hours,mins,secs);

    char buffer[MAXLINE];
    bzero(buffer, sizeof(buffer));
    sprintf(buffer, "Uptime: %dd:%dh:%dm:%ds\n",days,hours,mins,secs);
    sendto(udpfd, (const char*)buffer, sizeof(buffer), 0, 
           (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
	return time;
}

/**
* /proc/stat
* kernel/system statistics.  Varies with architecture.
* Ver https://www.kernel.org/doc/Documentation/filesystems/proc.txt (1.8)
*/
void showStats(int udpfd){
    FILE *fd;
    char ut[BUFFSIZE];
    char st[BUFFSIZE];
    char it[BUFFSIZE];
    char stat1[BUFFSIZE+1];
	char stat2[BUFFSIZE+1];
	char str1 [20];
	char str2 [20];
	char str3 [20];
	char str5 [20];
	char str6 [20];
    int flag1 = 1, flag2 = 1;

    fd = fopen("/proc/stat","r");
	fgets(stat1, BUFFSIZE+1, fd);

	//La cantidad de cpu puede variar, por ende no es seguro hacer fgets un numero fijo de veces
	//Por eso el while ejecuta fgets() hasta encontrar la primer linea que empiece con 'p',
	//que es la linea que contiene el valor buscado.
	while(!feof(fd)){
        fgets(stat2, BUFFSIZE+1, fd);

        if(strstr(stat2, "ctxt ") && flag1){
            sscanf(stat2,"%*s %s", str6);
            flag1 = 0;
        }
        if(strstr(stat2, "processes ") && flag2){
            sscanf(stat2,"%*s %s", str5);
            flag2 = 0;
        }
	}
	fclose(fd);
	fflush(fd);

    //Filtra los datos de uso del CPU y los imprime
    sscanf(stat1,"%*s %s %*s %s %s", str1, str2, str3);
    sprintf(ut, "UserTime: %s 1/100ths of a second\n",str1);
    sprintf(st, "SysTime: %s 1/100ths of a second\n",str2);
    sprintf(it, "IdleTime: %s 1/100ths of a second\n",str3);
    printf("%s", ut);
    printf("%s", st);
    printf("%s", it);
    sendto(udpfd, (const char*)ut, sizeof(ut), 0, 
           (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
    sendto(udpfd, (const char*)st, sizeof(st), 0, 
           (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
    sendto(udpfd, (const char*)it, sizeof(it), 0, 
           (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
    }

/**
* /proc/meminfo
* This file reports statistics about memory usage on the system.  It is used by free(1) to report the amount of free
* and used memory (both physical and swap) on the system as well as the shared memory and buffers used by the kernel.
* Each line of the file consists of a parameter name, followed  by  a colon, the value of the parameter, and an option
* unit of measurement (e.g., "kB").  The list below describes the parameter names and the format specifier required
* to read the field value.  Except as noted below, all of the fields have been present since at least Linux 2.6.0.
* Some fileds are only displayed if the kernel was configured with various options; those dependencies are noted in
* the list.
*/
void showMeminfo(int udpfd){
    FILE *fd;
    char freeMem[BUFFSIZE+1];
    char totalMem[BUFFSIZE+1];
	char meminfo1[BUFFSIZE+1];
	char meminfo2[BUFFSIZE+1];
	char str1 [20];

	fd = fopen("/proc/meminfo","r");
	fgets(meminfo1, BUFFSIZE+1, fd);
	fgets(meminfo2, BUFFSIZE+1, fd);
	fclose(fd);
	fflush(fd);

	//Filtra memoria total y la imprime
    sscanf(meminfo1,"%*s %s ", str1);
    printf("TotalMem: %s Kb\n",str1);
    sprintf(totalMem, "TotalMem: %s Kb\n",str1);
    sendto(udpfd, (const char*)totalMem, sizeof(totalMem), 0, 
           (struct sockaddr*)&cliaddr, sizeof(cliaddr));

    //Filtra memoria libre y la imprime
    sscanf(meminfo2,"%*s %s ", str1);
    printf("FreeMem: %s Kb\n",str1);
    sprintf(freeMem, "TotalMem: %s Kb\n",str1);
    sendto(udpfd, (const char*)freeMem, sizeof(freeMem), 0, 
           (struct sockaddr*)&cliaddr, sizeof(cliaddr));
}

/**
* Muestra la fecha y hora de inicio del sistema.
*/
void uptimeSystemDate(){
    FILE *in;
    extern FILE *popen();
    char buff[BUFFSIZE];

    in = popen("date -d \"`cut -f1 -d. /proc/uptime` seconds ago\"", "r");
    printf("Uptime system date: ");
    while(fgets(buff, sizeof(buff), in)!=NULL){
        printf("%s", buff);
    }
pclose(in);
}

/**
 * En matched coloca un puntero a la linea que comienza con la cadena especificada en matchStr.
 * @param filename Archivo donde se buscara la linea
 * @param matched Almacena la linea que comienza con la cadena matchStr.
 * @param matchStr Cadena a buscar.
 */
void findStr(char* filename, char* matched, char* matchStr){
	FILE* fd;
	char* findStr = NULL;
	char buffer[500];
	fd = fopen(filename,"r");

	while(feof(fd)==0){
		fgets(buffer, 500, fd);
		findStr = strstr(buffer, matchStr);
		if(findStr!=NULL)
			break;
	}
	fclose(fd);
	strcpy(matched,findStr);
}

// char * 	id(){
// 	FILE *fp = fopen("/proc/sys/kernel/hostname", "r");
// 	char buffer [TAM];
// 	memset( buffer, '\0', TAM );
// 	char * ptrBuff;
// 	int strsize = strlen(buffer) + 1;
// 	// We create dynamic pointer, if not, it gives core errors
// 	ptrBuff = (char*)malloc(strsize * sizeof(char));
// 	sprintf(ptrBuff, "%s", file2Str2(fp));
// 	// printf("%s", ptrBuff);
//     return ptrBuff;
// 	fclose(fp);
// }

// char * 	version(){
// 	FILE *fp = fopen("/proc/version", "r");
// 	char buffer [TAM];
// 	char *version;
// 	memset( buffer, '\0', TAM );
// 	char * ptrBuff;
// 	int strsize = strlen(buffer) + 1;
// 	// We create dynamic pointer, if not, it gives core errors
// 	ptrBuff = (char*)malloc(strsize * sizeof(char));
// 	version = file2Str(fp);
// 	loadReg2(lreg,version);
// 	sprintf(ptrBuff, "%s",find(lreg, "version"));
//     return ptrBuff;
// 	fclose(fp);
// }

// char * 	UpTime(){
// 	FILE *fp = fopen("/proc/uptime", "r");
// 	char buffer [TAM];
// 	char * ptrBuff;
//     char * str;
//     int totalSec;
// 	int t = time(NULL);
// 	memset( buffer, '\0', TAM );
// 	int strsize = strlen(buffer) + 1;
// 	// We create dynamic pointer, if not, it gives core errors
// 	ptrBuff = (char*)malloc(strsize * sizeof(char));
// 	str = file2Str(fp);
// 	loadReg2(lreg,str);
// 	totalSec = atoi(str);
// 	time_t raw_time = t - totalSec;
// 	struct tm * timeinfo;
// 	timeinfo = localtime (&raw_time);
// 	strftime (buffer, 80, "%x %X",timeinfo);
//     sprintf(ptrBuff, "%s", buffer);
//     return ptrBuff;
// 	fclose(fp);
// }

// char * 	secondsToDHMS(int sec){
// 	char buffer [TAM];
// 	memset( buffer, '\0', TAM );
// 	char * ptrBuff;
// 	int strsize = strlen(buffer) + 1;
// 	// We create dynamic pointer, if not, it gives core errors
// 	ptrBuff = (char*)malloc(strsize * sizeof(char));
    
// 	int seconds = (sec % 60);
// 	int minutes = (sec % 3600) / 60;
// 	int hours = (sec % 86400) / 3600;
// 	int days = (sec % (86400 * 30)) / 86400;
// 	sprintf(ptrBuff, "%dD %d:%d:%d", days, hours, minutes, seconds);
//     return ptrBuff;
// }

// char * 	userTime(){
//     char buffer [TAM];
// 	memset( buffer, '\0', TAM );
// 	char * ptrBuff;
// 	char * ptr;
// 	int strsize = strlen(buffer) + 1;
// 	// We create dynamic pointer, if not, it gives core errors
// 	ptrBuff = (char*)malloc(strsize * sizeof(char));
// 	FILE *fp = fopen("/proc/stat", "r");
// 	ptr = file2Str(fp);
// 	loadReg2(lreg, ptr);
// 	int userTime = atoi(lreg[1])/100;
// 	secondsToDHMS(userTime);
//     sprintf(ptrBuff, "userTime: %s", secondsToDHMS(userTime));
//     // printf("Tam: %lu", strlen(ptrBuff));
// 	fclose(fp);
//     return ptrBuff;
// }

// char * 	sysTime(){
//     char buffer [TAM];
// 	memset( buffer, '\0', TAM );
// 	char * ptrBuff;
// 	char * ptr;
// 	int strsize = strlen(buffer) + 1;
// 	// We create dynamic pointer, if not, it gives core errors
// 	ptrBuff = (char*)malloc(strsize * sizeof(char));
// 	FILE *fp = fopen("/proc/stat", "r");
// 	ptr = file2Str(fp);
// 	loadReg2(lreg, ptr);
// 	int sysTime = atoi(lreg[2])/100;
// 	secondsToDHMS(sysTime);
//     sprintf(ptrBuff, "sysTime: %s", secondsToDHMS(sysTime));
//     // printf("Tam: %lu", strlen(ptrBuff));
// 	fclose(fp);
//     return ptrBuff;
// }

// char * 	idleTime(){
//     char buffer [TAM];
// 	memset( buffer, '\0', TAM );
// 	char * ptrBuff;
// 	char * ptr;
// 	int strsize = strlen(buffer) + 1;
// 	// We create dynamic pointer, if not, it gives core errors
// 	ptrBuff = (char*)malloc(strsize * sizeof(char));
// 	FILE *fp = fopen("/proc/stat", "r");
// 	ptr = file2Str(fp);
// 	loadReg2(lreg, ptr);
// 	int idleTime = atoi(lreg[3])/100;
// 	secondsToDHMS(idleTime);
//     sprintf(ptrBuff, "idleTime: %s", secondsToDHMS(idleTime));
//     // printf("Tam: %lu", strlen(ptrBuff));
// 	fclose(fp);
//     return ptrBuff;
// }

// char * 	mem(){
// 	FILE *fp = fopen("/proc/meminfo", "r");
// 	char buffer [TAM];
// 	char * ptrBuff;
// 	char * str;
// 	memset( buffer, '\0', TAM );
// 	int strsize = strlen(buffer) + 1;
// 	// We create dynamic pointer, if not, it gives core errors
// 	ptrBuff = (char*)malloc(strsize * sizeof(char));
// 	str = file2Str(fp);
// 	loadReg2(lreg, str);
// 	sprintf(ptrBuff, "%s/%s",find(lreg,"MemFree"),find(lreg,"MemTotal"));
// 	fclose(fp);
//     return ptrBuff;
// }