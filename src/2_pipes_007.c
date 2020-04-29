// В текущем каталоге есть 2 канала in1 in2, в которые в случайном порядке поступают числа, 
// которые необходимо просуммировать и вывести окончательную сумму на экран. Сумма выводится в 
// отдельной строке, завершающейся символом конца строки. Признаком окончания подачи символов в 
// каналы является закрытие этих каналов посылающей стороной.

// Подсказка: для неблокирующего чтения использовать select.
// Замечание: ﻿протокол обмена по каналу текстовый, то есть числа представлены строками


#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>

int main()
{
    int fds[2];
    char buf[4096];
    int i, rc, maxfd;
    fd_set watchset;
    fd_set inset; 
    int counter = 0; 

    if ((fds[0] = open("in1", O_RDONLY | O_NONBLOCK)) < 0) {
        perror("open p1");
        return 1;
    }

    if ((fds[1] = open("in2", O_RDONLY | O_NONBLOCK)) < 0) {
        perror("open p2");
        return 1;
    }

    FD_ZERO(&watchset);
    FD_SET(fds[0], &watchset);
    FD_SET(fds[1], &watchset);

    maxfd = fds[0] > fds[1] ? fds[0] : fds[1];

    while (FD_ISSET(fds[0], &watchset) || FD_ISSET(fds[1], &watchset)) 
    {
        inset = watchset;
        if (select(maxfd + 1, &inset, NULL, NULL, NULL) < 0) 
        {
            perror("select");
            return 1;
        } 

        for (i = 0; i < 2; i++) 
        {
            if (FD_ISSET(fds[i], &inset)) 
            {
                rc = read(fds[i], buf, sizeof(buf) - 1);

                if (rc < 0) 
                {
                    perror("read");
                    return 1;
                } 
                
                else if (rc == 0) 
                {
                    close(fds[i]);
                    FD_CLR(fds[i], &watchset);
                }

                else 
                {
                    buf[rc] = '\0';
                    counter += atoi(buf);
                }
            }
        } 
    }

    printf("%d\n", counter);

    return 0;
}