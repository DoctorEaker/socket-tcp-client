#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include "yacurl.h"

#define BUFFER_LIMIT 4096

int main(int argc, char *argv[])
{
    unsigned short server_port = 80; /* The port the client will try to connect to */
    yacurl_st *tcp_client;

    if (argc < 2 || argc > 3)
    {
        fprintf(stderr, "[Error] Usage: %s <Host> [PortNumber]\n", argv[0]);
        exit(1);
    }
    else if (argc == 3)
    {
        server_port = (unsigned short)atoi(argv[2]);
    }

    yacurl_constructor(argv[1], server_port, tcp_client);

    return 0;
}