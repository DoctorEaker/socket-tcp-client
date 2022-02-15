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

parsed_url_st *yacurl_getParsedUrl(yacurl_st *yacurl)
{
    return yacurl->url_parsed;
}

void yacurl_constructor(char *url, unsigned short port, yacurl_st *yacurl)
{
    parsed_url_st *parsed_url;

    yacurl = (yacurl_st *)malloc(sizeof(yacurl_st));

    parsed_url = (parsed_url_st *)malloc(sizeof(parsed_url_st));
    parse_url(url, parsed_url);

    yacurl->url_parsed = parsed_url;
    if (url_getPort(yacurl_getParsedUrl(yacurl)) != port)
    {
        printf("Using port in the url: %d \n", url_getPort(yacurl->url_parsed));
    }
}