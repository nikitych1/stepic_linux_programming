// Требуется написать программу solution, выполняющую разбор опций командной строки
// и выводящую в стандартный поток вывода символ '+', если набор корректен, 
// или '-' в противном случае.

// Описание возможных опций:

//     -q | --query (опциональный, но обязательно требует аргумента)
//     -i | --longinformationrequest (опциональный)
//     -v | --version (опциональный)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

struct globalArgs_t 
{
	const char * query;				
	const char * longinformationrequest;				
	const char * version;	

} globalArgs;

static const char *optString = "q:iv";

static const struct option longOpts[] = {
	{ "query", required_argument, NULL, 'q' },
	{ "longinformationrequest", optional_argument, NULL, 'i' },
	{ "version", optional_argument, NULL, 'v' },
    { 0, 0, 0, 0 }
};

char stat[4];

int main(int argc, char *argv[])
{
    extern int opterr;
    opterr = 0;
    
	int opt = 0;
	int longIndex = 0;
	
	globalArgs.query = "";
	globalArgs.longinformationrequest = "";
	globalArgs.version = "";

	opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
    
    stat[3] = '1';

	while( opt != -1 ) 
    {
		switch (opt) 
        {
            case 'q':
				stat[0] = '1';
                printf("q");
				break;			
            
            case 'i':
				stat[1] = '1';
                printf("i");
				break;			
            
            case 'v':
                stat[2] = '1';
                printf("v");
				break;

			case '?':
                stat[3] = '0';
                printf("?");
				break;
		}
		
		opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
	}

    int res = 1;
    size_t i = 0;

    for (i; i < 4; i++)
    {
        printf(" %c ", stat[i]);
        if (stat[i] == '0') res = 0;
    }

    if (res == 1)
        printf("+\n");
    else
        printf("-\n");

	return EXIT_SUCCESS;
}