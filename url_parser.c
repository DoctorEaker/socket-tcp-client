#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdbool.h>

typedef struct
{
    char *host;
    unsigned short port;
    char *resource_path;
    char *protocol;
} parsed_url_st;

void free_parsed_url(parsed_url_st *url_parsed)
{
    if (url_parsed->protocol)
        free(url_parsed->protocol);
    if (url_parsed->host)
        free(url_parsed->host);
    if (url_parsed->resource_path)
        free(url_parsed->resource_path);

    free(url_parsed);
}

static inline void parse_port(parsed_url_st *parsed_url, char **token_url_pointer)
{
    char *token_host;

    token_host = strtok_r(NULL, ":", token_url_pointer);
    if (token_host)
        parsed_url->port = atoi(token_host);
    else
        parsed_url->port = 80;

    token_host = strtok_r(NULL, ":", token_url_pointer);
    assert(token_host == NULL);
}

static inline void parse_host(parsed_url_st *parsed_url, char *host_port, char **token_url_pointer)
{
    char *token_host;

    token_host = strtok_r(host_port, ":", token_url_pointer);

    if (token_host)
    {
        parsed_url->host = (char *)malloc(sizeof(char) * strlen(token_host) + 1);
        strcpy(parsed_url->host, token_host);
    }
    else
    {
        parsed_url->host = NULL;
    }
}

static inline void parse_host_port(parsed_url_st *parsed_url, char **token_url_pointer)
{
    char *token;
    char *host_port;
    char *token_host_pointer;

    token = strtok_r(NULL, "/", token_url_pointer);

    if (token)
    {
        host_port = (char *)malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(host_port, token);
    }
    else
    {
        host_port = (char *)malloc(sizeof(char) * 1);
        strcpy(host_port, "");
    }

    parse_host(parsed_url, host_port, &token_host_pointer);
    parse_port(parsed_url, &token_host_pointer);
}

static inline void parse_protocol(parsed_url_st *parsed_url, char **token_url_pointer, char *url)
{
    char *token;
    token = strtok_r(url, ":", token_url_pointer);
    parsed_url->protocol = (char *)malloc(sizeof(char) * strlen(token) + 1);
    strcpy(parsed_url->protocol, token);
}

static inline void parse_path(parsed_url_st *parsed_url, char **token_url_pointer)
{
    char *token;
    token = strtok_r(NULL, "?", token_url_pointer);
    parsed_url->resource_path = NULL;
    if (token)
    {
        parsed_url->resource_path = (char *)malloc(sizeof(char) * (strlen(token) + 1));
        strncpy(parsed_url->resource_path, token, strlen(token));
    }
    else
    {
        parsed_url->resource_path = (char *)malloc(sizeof(char) * 2);
        strcpy(parsed_url->resource_path, "/");
    }
}

int parse_url(char *url, parsed_url_st *parsed_url)
{
    char *_url = (char *)malloc(sizeof(char) * (strlen(url) + 1));
    char *_path = NULL;
    char *token_url_pointer;

    strcpy(_url, url);

    parse_protocol(parsed_url, &token_url_pointer, _url);
    parse_host_port(parsed_url, &token_url_pointer);
    parse_path(parsed_url, &token_url_pointer);

    return 0;
}
