#ifndef YACURL_H_
#define YACURL_H_
#include <netinet/in.h>
#include "url_parser.h"

typedef struct
{
    int sockfd;                        /* Socker File Descriptor */
    int numbytes;                      /* Number of bytes read in the buffer */
    unsigned short server_port;        /* The port the client will try to connect to */
    struct sockaddr_in server_address; /* Server Address */
    struct hostent *host_info;         /* Host Information */
    parsed_url_st *url_parsed;

} yacurl_st;

void yacurl_constructor(char *url, unsigned short port, yacurl_st *yacurl);

#endif