#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

DIR * p_dir;
struct dirent *p_dirent_s;
char path[50];

char* current_pid;

void readFile(char* start_pid)
{
    sprintf (path, "/%s/%s/%s", "proc", start_pid, "stat");

    FILE *fp;
    char *line, *token;
    size_t len = 0, i = 0;
    ssize_t read = 0;

    fp = fopen(path, "r");
 
    if (fp == NULL) {
        printf("%s\n", "error f i/o");
        return;
    }

	getline(&line, &len, fp);

    token = strtok(line, " ");

	while (i < 4)
	{
		token = strtok(NULL, " ");
	
		if (i == 2) 
        {
            printf("%s\n", token);

            if (strcmp(token, "1") == 0)
                return;

            readFile(token);         
        }

		++i;
	}

    fclose(fp);
}

int main(int argc, char** argv)
{
    printf("%s\n", argv[1]);
    readFile(argv[1]);

	return 0;
}