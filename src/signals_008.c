// Разработать приложение, умеющее обрабатывать сигналы SIGUSR1 ,SIGUSR2, SIGTERM. 
// После старта Ваше приложение должно по приходу одного из сигналов SIGUSR1,  
// SIGUSR2 выполнять суммирование числа срабатываний каждого из сигналов, 
// а после прихода сигнала SIGTERM, требуется вывести в стандартный поток вывода 2 числа, 
// разделенных пробелом, соответствующих количеству обработанных сигналов 
// SIGUSR1, SIGUSR2, и завершить программу. 
// Вывод оканчивается символом конца строки.

// #include <stdio.h>
// #include <signal.h>
// #include <string.h>

#include <errno.h>
#include <sys/signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

volatile size_t su1_counter = 0;
volatile size_t su2_counter = 0;

void sigusr1_handler()
{
    su1_counter++;
}

void sigusr2_handler()
{
    su2_counter++;
}

void sigterm_handler()
{
    printf("%zu %zu\n", su1_counter, su2_counter);
    exit(0);
}

void common_handler(int signum)
{
    printf("%d\n", signum);
    // switch(signum)
    // {
    //     case 10:
    //         sigusr1_handler();
    //         break;
    //     case 12:
    //         sigusr2_handler();
    //         break;
    //     case 15:
    //         sigterm_handler();
    //         break;
    // }
}

int main()
{
    struct sigaction sa;
    sigset_t set; 

    memset(&sa, 0, sizeof(sa)); 
    sa.sa_handler = common_handler;

    sigemptyset(&set); 

    sigaddset(&set, SIGUSR1); 
    sigaddset(&set, SIGUSR2);
    sigaddset(&set, SIGTERM);
    sigaddset(&set, SIGURG);


    sa.sa_mask = set;

    sigaction(SIGUSR1, &sa, 0);
    sigaction(SIGUSR2, &sa, 0);
    sigaction(SIGTERM, &sa, 0);
    sigaction(SIGURG, &sa, 0);


    while (1) {}

    return 0;
}   