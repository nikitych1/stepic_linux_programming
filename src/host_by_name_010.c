#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>

#include <stdlib.h>
#include <stdio.h>

struct hostent* he;

int main(int argc, char** argv)
{
    he = gethostbyname(argv[1]);

    size_t i = 0;
    while(NULL != he->h_addr_list[i])
    {
        printf( "%s\n", inet_ntoa( *( struct in_addr*)(he -> h_addr_list[i])));
        i++;
    }

	return 0;
}