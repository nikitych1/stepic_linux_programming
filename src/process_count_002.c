#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

size_t i = 0;
DIR * p_dir;
struct dirent *p_dirent_s;

size_t count_proc = 0;
char res[50], *proc_name = "genenv";

void readFile(char *path)
{
    FILE *fp;
    char *line, *token;
    size_t len = 0;
    ssize_t read = 0;

    fp = fopen(path, "r");
 
    if (fp == NULL)
        exit(EXIT_FAILURE);

	getline(&line, &len, fp);

	token = strtok(line, " ()");
    token = strtok(NULL, " ()");
    // printf("%s\n", token);

    if (strcmp(token, proc_name) == 0) ++count_proc;      

    fclose(fp);
}

int main()
{
    char * path = "/proc";
    p_dir = opendir(path);

    if (p_dir == NULL) {
        printf ("Cannot open directory '%s'\n", path);
        return 1;
    }

    while ((p_dirent_s = readdir(p_dir)) != NULL) {
        if (isdigit(p_dirent_s->d_name[0]))
        {
            sprintf (res, "%s/%s/%s", path, p_dirent_s->d_name, "stat");
            readFile(res);
        }
    }

    printf("%zu\n", count_proc);
 
    closedir (p_dir);

	return 0;
}