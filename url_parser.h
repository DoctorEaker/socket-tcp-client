#ifndef FOO_H_ /* Include guard */
#define FOO_H_

typedef struct
{
    char *host;
    unsigned short port;
    char *resource_path;
    char *protocol;
} parsed_url_st;

int parse_url(char *url, parsed_url_st *parsed_url);

#endif // FOO_H_
