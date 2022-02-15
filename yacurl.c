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

#define BUFFER_LIMIT 8192

parsed_url_st *yacurl_getParsedUrl(yacurl_st *yacurl)
{
    return yacurl->url_parsed;
}

void initialize_sockaddr_in(yacurl_st *yacurl)
{
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(yacurl->server_port);
    server_address.sin_addr = *((struct in_addr *)yacurl->host_info->h_addr);
    memset(&(server_address.sin_zero), '\0', 8);
    yacurl->server_address = server_address;
}

void yacurl_connect(yacurl_st *yacurl)
{
    if (connect(yacurl->sockfd, (struct sockaddr *)&(yacurl->server_address), sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        exit(1);
    };
}

void yacurl_constructor(char *url, unsigned short port, yacurl_st *yacurl)
{
    parsed_url_st *parsed_url;
    struct sockaddr_in server_address;

    yacurl = (yacurl_st *)malloc(sizeof(yacurl_st));

    parsed_url = (parsed_url_st *)malloc(sizeof(parsed_url_st));
    parse_url(url, parsed_url);

    yacurl->url_parsed = parsed_url;

    if ((yacurl->sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    if (url_getPort(yacurl_getParsedUrl(yacurl)) != port && url_getPort(yacurl_getParsedUrl(yacurl)) != 80)
    {
        printf("Using port in the url: %d \n", url_getPort(yacurl->url_parsed));
        yacurl->server_port = url_getPort(yacurl->url_parsed);
    }
    else
    {
        yacurl->server_port = port;
    }

    if ((yacurl->host_info = gethostbyname(gethostbyname(yacurl->url_parsed->host))) == NULL)
    {
        herror("gethostbyname");
        exit(1);
    }

    initialize_sockaddr_in(yacurl);
}