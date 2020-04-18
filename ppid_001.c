#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

char* token;

int main()
{
	// printf("%d\n", getppid());
	// printf("\n");


	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("/proc/self/stat", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

	getline(&line, &len, fp);

	token = strtok(line, " ");

	size_t i = 0;
	while (i < 10){
		token = strtok(NULL, " ");
		if (i == 2)
			printf("%s\n", token);
		++i;
	}

	// printf("\n");

    fclose(fp);

    if (line)
        free(line);

    exit(EXIT_SUCCESS);

	return 0;
}