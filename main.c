#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include "url_parser.h"

#define BUFFER_LIMIT 4096

int main(int argc, char *argv[])
{

    int sockfd,                        /* Socker File Descriptor */
        numbytes;                      /* Number ofya bytes read in the buffer */
    unsigned short server_port = 80;   /* The port the client will try to connect to */
    struct sockaddr_in server_address; /* Server Address */
    struct hostent *host_info;         /* Host Information */

    char buf[BUFFER_LIMIT];

    if (argc < 2 || argc > 3)
    {
        fprintf(stderr, " Usage: %s <Host> [PortNumber]\n", argv[0]);
        exit(1);
    }
    else if (argc == 3)
    {
        server_port = (unsigned short)atoi(argv[2]);
    }

    char host[BUFFER_LIMIT];
    char page[BUFFER_LIMIT];
    sscanf(argv[1], "http://%99[/]%99[^\n]", host, page);
    printf("Host name  : %s\n", host_info->h_name);
    printf("Resource  : %s\n", page);

    if ((host_info = gethostbyname(host)) == NULL)
    {
        herror("gethostbyname");
        exit(1);
    }

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    server_address.sin_addr = *((struct in_addr *)host_info->h_addr);
    memset(&(server_address.sin_zero), '\0', 8);

    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        exit(1);
    };

    char inputBuffer[BUFFER_LIMIT] = {0};
    char outputBuffer[BUFFER_LIMIT - 4] = {0};

    fprintf(stderr, "[INFO] Connection established succesfully.");
    printf("Host name  : %s\n", host_info->h_name);
    printf("Resource  : %s\n", page);
    fprintf(stderr, "\n[INFO] Type \'EXIT\' to disconnect.\n");

    while (1)
    {
        fprintf(stderr, "> ");

        // snprintf(outputBuffer, BUFFER_LIMIT,
        // "GET %s HTTP/1.0\r\n"  // POST or GET, both tested and works. Both HTTP 1.0 HTTP 1.1 works, but sometimes
        // "Host: %s\r\n"     // but sometimes HTTP 1.0 works better in localhost type
        // "Content-type: application/x-www-form-urlencoded\r\n"
        // "Content-length: %d\r\n\r\n"
        // "%s\r\n", argv[1], host, (unsigned int)strlen(poststr), poststr);

        if (send(sockfd, outputBuffer, strlen(outputBuffer), 0) == -1)
        {
            perror("send");
            exit(1);
        }

        // Receive a message from client
        int readBytes = recv(sockfd, inputBuffer, sizeof(inputBuffer) - 1, 0);
        if (readBytes < 0)
        {
            perror("recv");
            exit(1);
        }

        inputBuffer[readBytes] = 0;
        fprintf(stderr, "[INFO] Received a message from server: %s\n", inputBuffer);
        memset(inputBuffer, 0, BUFFER_LIMIT);

        if (strcmp("EXIT", outputBuffer) == 0)
        {
            break;
        }
        else if (strncmp("GET", outputBuffer, 3) == 0)
        {

            // Receive file stream
            fprintf(stderr, "> Save to: ");
            scanf("%s", outputBuffer);
            FILE *outputFile = fopen(outputBuffer, "wb");

            int readBytes = 0;
            while ((readBytes = recv(sockfd, inputBuffer, BUFFER_LIMIT, 0)) > 0)
            {
                fprintf(stderr, "[INFO] Received %lu bytes\n", strlen(inputBuffer));
                fwrite(inputBuffer, sizeof(char), readBytes, outputFile);
                memset(inputBuffer, 0, BUFFER_LIMIT);

                if (readBytes < BUFFER_LIMIT)
                {
                    break;
                }
            }
            fclose(outputFile);
        }
        else
        {
            // Receive a message from client
            int readBytes = recv(sockfd, inputBuffer, BUFFER_LIMIT, 0);
            if (readBytes < 0)
            {
                perror("recv");
                exit(1);
            }
            fprintf(stderr, "[INFO] Received a message from server: %s\n", inputBuffer);
            memset(inputBuffer, 0, BUFFER_LIMIT);
        }
    }

    close(sockfd);

    return 0;
}