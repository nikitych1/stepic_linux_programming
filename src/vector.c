#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct StringVector StringVector, *vector;
struct StringVector 
{
    size_t _size;
    char** _data;

    void (*init)(StringVector *, size_t init_size);
    void (*push_back)(StringVector *);
    void (*clear)(StringVector *);
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

    for (size_t i = 0; i < size; ++i) 
        free((*self)._data[i]);

    free((*self)._data);
}

int main(int argc, char** argv)
{
    StringVector s_vector;
    init(&s_vector, 1024);

    for (size_t i = 0; i < 5; ++i)
        push_back(&s_vector, "ыва");

    for (size_t i = 0; i < s_vector._size; ++i)
        printf("%s ", s_vector._data[i]);

    printf("\n");

    clear(&s_vector);

	return 0;
}