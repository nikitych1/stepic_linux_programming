// Разработайте TCP сервер, предназначенный для сортировки символов в строке.
// Сервер получает на вход строки, оканчивающиеся символом '\0', сортирует в 
// них символы в порядке убывания ASCII-кодов и отсылает обратно на клиент, в
// виде строки заканчивающейся '\0'. Завершение работы сервера происходит после 
// получения строки, содержащей только 'OFF'. 

// При старте сервер получает на вход номер порта в качестве параметра командной строки. 
// bind производится на адресе 127.0.0.1

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void swap(char *xp, char *yp) 
{ 
    char* temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void bubbleSort(char* str, int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
       for (j = 0; j < n-i-1; j++)  
           if (str[j] < str[j+1]) 
              swap(&str[j], &str[j+1]); 
} 

void sort_and_print(int sfd) 
{ 
    char buff[5120];
    memset(buff, 0, sizeof(buff));

    while(1)
    { 
        if (strncmp("OFF", buff, 3) == 0) exit(0);

        if (0 < strcmp(buff, ""))
            write(sfd, buff, sizeof(buff));

        size_t n = read(sfd, buff, sizeof(buff));
        size_t i = 0, j = 0;

        bubbleSort(buff, n);
    } 
} 

int main(int argc, char** argv)
{
    struct sockaddr_in my_addr, peer_addr;
    int sfd;

    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket down");
        exit(EXIT_FAILURE);
    }

    memset(&my_addr, 0, sizeof(struct sockaddr_in));
    memset(&peer_addr, 0, sizeof(struct sockaddr_in));

    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); 
    my_addr.sin_port = htons(atoi(argv[1]));

    if (bind(sfd, (const struct sockaddr *) &my_addr, sizeof(my_addr)) < 0) {
        perror("bind down");
        exit(EXIT_FAILURE);
    }

    if ((listen(sfd, 5)) != 0) { 
        perror("listen down"); 
        exit(EXIT_FAILURE); 
    } 

    int len, n; 
    len = sizeof(peer_addr);

    int connfd = accept(sfd, (struct sockaddr*) &peer_addr, &len);

    if (connfd < 0) 
    { 
        close(sfd);
        perror("accept down"); 
        exit(EXIT_FAILURE); 
    } 

    sort_and_print(connfd);

    close(sfd);

	return 0;
}