#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <malloc.h>
#include <string.h>

// #include "vector.h"

typedef struct StringVector StringVector, *vector;
struct StringVector 
{
    size_t _size;
    char** _data;
};

void init(StringVector *self, size_t init_size) 
{ 
    (*self)._size = 0;
    (*self)._data = (char**) malloc(sizeof(char*) * init_size);
}

void push_back(StringVector *self, char* string) 
{
    size_t size = (*self)._size;

    (*self)._data[size] = malloc(sizeof(char)* strlen(string));
    strcpy((*self)._data[size], string);
    ++(*self)._size;
}

void clear(StringVector *self)
{
    size_t size = (*self)._size;
    size_t i =0;
    for (i = 0; i < size; ++i) 
        free((*self)._data[i]);

    free((*self)._data);
}

char* back(StringVector *self)
{
    size_t size = (*self)._size;
    char* back_item = malloc(sizeof(char) * strlen((*self)._data[size - 1]));
    strcpy(back_item, (*self)._data[size - 1]);
    return back_item;
}

DIR * p_dir;
struct dirent *p_dirent_s;
char path[50];

size_t counter = 1;
char* current_pid;

StringVector s_vector;

void readFile(char* start_pid)
{
    sprintf (path, "/%s/%s/%s/%s/%s", "proc", start_pid, "task", start_pid, "children");

    FILE *fp;
    char *line, *token;
    size_t len = 0, i = 0;
    ssize_t read = 0;

    fp = fopen(path, "r");
 
    if (fp == NULL) {
        printf("%s\n", "error f i/o");
        return;
    }
    ++counter;

	getline(&line, &len, fp);
    // printf("   %s : [%s]\n", start_pid, line);

    token = strtok(line, " ");

    while (token != NULL) 
    { 
        push_back(&s_vector, token);
        token = strtok(NULL, " ");
    }

    fclose(fp);
}

int main(int argc, char** argv)
{
    init(&s_vector, 1024);

    readFile(argv[1]);

    if (s_vector._size > 0) 
    {
        // printf("\n   v : [");

        // for (size_t i = 0; i < s_vector._size; ++i)
        //     printf("%s, ", s_vector._data[i]);

        size_t i = 0;
        for (i = 0; i < s_vector._size; ++i)
        {
            // printf("\nback = %s", s_vector._data[i]);
            // printf("]; size = |%zu|\n", s_vector._size);

            readFile(s_vector._data[i]);
        }
    }

    printf("%zu\n", s_vector._size + 1);


    clear(&s_vector);

	return 0;
}