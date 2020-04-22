#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    size_t pid = getpid();
    printf("%zu\n", pid);

    size_t id = fork();

    if (id == 0)
        setsid();

    else
    {
        fclose(stdin);
        fclose(stdout);
        fclose(stderr);
        daemon(0, 0);
        sleep(50000);
    }

    BUFSIZ

	return 0;
}