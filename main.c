#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>	

#define BUFFER_LIMIT 4096

int main(int argc, char *argv[]) {

    int sockfd,    /* Socker File Descriptor */
        numbytes,  /* Number of bytes read in the buffer */
        server_port = 80; /* The port the client will try to connect to */
    struct sockaddr_in server_address; /* Server Address */
    struct hostent *host_info; /* Host Information */
    
    char buf[BUFFER_LIMIT];

    if ( argc < 2 || argc > 3  ) {
        fprintf(stderr," Usage: %s <Host> [PortNumber]\n",argv[0]);
        exit(1);
    } else if (argc == 3){
        server_port = argv[2];
    }

    if ((host_info=gethostbyname(argv[1])) == NULL) {
        herror("gethostbyname");
        exit(1);
    }

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0))== -1){
        perror("socket");
        exit(1);
    }

    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(server_port);
    server_address.sin_addr = *((struct in_addr *)host_info->h_addr);
    memset(&(server_address.sin_zero),'\0', 8);

    if(connect(sockfd, (struct sockaddr *)&server_address, sizeof(struct sockaddr)) == -1 ){
       perror("connect");
       exit(1);
    };

    if ((numbytes=recv(sockfd, buf, BUFFER_LIMIT-1, 0)) == -1) {
        perror("recv");
        exit(1);
    }

    buf[numbytes] = '\0';

    printf("Received: %s",buf);

    close(sockfd);

    return 0;
}