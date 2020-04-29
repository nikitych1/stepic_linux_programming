#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void urg_handler(int signum)
{   
    exit(signum);
} 


int main(int argc, char** argv)
{
    struct sigaction sa;
    sigset_t set; 

    memset(&sa, 0, sizeof(sa)); 
    sa.sa_handler = urg_handler;

    sigemptyset(&set); 
    sigaddset(&set, SIGURG); 


    sa.sa_mask = set;

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

        sigaction(SIGURG, &sa, 0);

        while(1) {  }
    }

	return 0;
}