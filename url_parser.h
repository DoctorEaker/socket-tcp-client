#ifndef URL_PARSER_H_
#define URL_PARSER_H_

typedef struct
{
    char *host;
    unsigned short port;
    char *resource_path;
    char *protocol;
} parsed_url_st;

int parse_url(char *url, parsed_url_st *parsed_url);
char *url_getHost(parsed_url_st *parsed_url);
unsigned short url_getPort(parsed_url_st *parsed_url);
char *url_getProtocol(parsed_url_st *parsed_url);
char *url_getPath(parsed_url_st *parsed_url);

#endif
