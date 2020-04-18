#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

char* token;
size_t i = 0;

int main()
{
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("/proc/self/stat", "r");
 
    if (fp == NULL)
        exit(EXIT_FAILURE);

	getline(&line, &len, fp);

	token = strtok(line, " ");

	while (i < 10)
	{
		token = strtok(NULL, " ");
	
		if (i == 2)
			printf("%s\n", token);

		++i;
	}

    fclose(fp);

    if (line)
        free(line);

    exit(EXIT_SUCCESS);

	return 0;
}