#include "server_tcp.h"
#include "header.h"
#include "hash-string.h"

// KEYS
#define HASH 3378490201
#define UFB 522895564
#define SS 3318239844
#define OT 3707994656
#define HELP 1950366504
#define EXIT 2090237503

// COLORS
#define GREEN       "\x1b[32m"
#define RESETCLR    "\x1b[0m"
#define BOLD        "\033[1m"
#define RESETBOLD   "\033[0m"

int main() {
	//printf("IP: %s", getIP());
	(run()==1) ? createSocketTCP() : exit(1); 
	// updateFirmware();
	// createSocketTCP();
	
	return 0; 
}