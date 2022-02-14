#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>	

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {

    if ( argc < 2 || argc > 3  ) {
        fprintf(stderr," Usage: %s <Host> [PortNumber]\n",argv[0]);
        return EXIT_FAILURE;
    }

    return 0;
}