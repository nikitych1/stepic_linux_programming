// Разработайте UDP сервер для логирования (сбора и записи) сообщений. 
// Сервер при запуске принимает параметр -- номер порта, на котором 
// будут приниматься запросы. Каждый запрос приходящий к серверу - строка, 
// не превышающая размер 5K.  Задача сервера -- выводить приходящие строки 
// в стандартный поток ввода-вывода, завершающиеся символом конца строки.

// Сервер завершает работу, когда получает строку содержащую только текст 'OFF',
// и заканчивающуюся символом перевода строки '\n'. 

// Сервер использует локальный адрес 127.0.0.1

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    struct sockaddr_in my_addr, peer_addr;
    char buf[5120];
    int sfd;

    if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket down");
        exit(EXIT_FAILURE);
    }

    memset(&my_addr, 0, sizeof(struct sockaddr_in));

    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); 
    my_addr.sin_port = htons(atoi(argv[1])); 

    if (bind(sfd, (const struct sockaddr *) &my_addr, sizeof(my_addr)) < 0) {
        perror("bind down");
        exit(EXIT_FAILURE);
    }

    int len, n; 
    len = sizeof(peer_addr);

    while(0 != strcmp(buf, "OFF\n"))
    {
        if (0 < strcmp(buf, ""))
            printf("%s\n", buf);

        n = recvfrom(sfd, (char *)buf, 5120, MSG_WAITALL, ( struct sockaddr *) &peer_addr, &len); 
        buf[n] = '\0';
    }
  
	return 0;
}