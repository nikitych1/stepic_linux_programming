// В системе существуют 2 региона разделяемой памяти, заполненной некоторыми 
// числами (типа int). Каждый из регионов имеет размер 1000 байт. Вам 
// требуется разработать приложение, которое попарно суммирует первые 100 чисел
// в этих регионах и помещает суммы в новый (созданный вашим приложением) 
// регион памяти размером 1000 байт. Таким образом, после завершения работы 
// Вашего приложения в памяти должен существовать регион разделяемой памяти 
// размером 1000 байт, содержащий в начале 100 сумм. Перед завершением работы 
// приложение выводит в стандартный поток ввода-вывода ключ созданного региона, 
// завершающийся символом конца строки. 
// На вход ваше приложение принимает ключи существующих регионов памяти.

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int shm_id, shm_id_1, shm_id_2;
int * shm_buf_1, *shm_buf_2, *shm_buf;
struct shmid_ds ds;

int main(int argc, char** argv)
{
    shm_id_1 = shmget((key_t) atoi(argv[1]), 1000 * sizeof(char), IPC_CREAT | 0666);
    shm_id_2 = shmget((key_t) atoi(argv[2]), 1000 * sizeof(char), IPC_CREAT | 0666);


    shm_buf_1 = (int *) shmat(shm_id_1, 0, 0);
    shm_buf_2 = (int *) shmat(shm_id_2, 0, 0);

    if (shm_buf_1 == (int *) -1) {
        fprintf (stderr, "shmat() error\n");
        return 1;
    }

    shm_id = shmget(54321, 1000 * sizeof(char), IPC_CREAT | 0666);

    if (shm_id == -1) {
        fprintf (stderr, "shmget() error\n");
        return 1;
    }

    shm_buf = (int *) shmat(shm_id, NULL, 0);

    if (shm_buf == (int *) -1) {
        fprintf (stderr, "shmat() error\n");
        return 1;
    }

    printf("%d\n", 54321);

    for (size_t iter = 0; iter < 100; ++iter)
        shm_buf[iter] = shm_buf_1[iter] + shm_buf_2[iter];

    shmdt(shm_buf);
    shmdt(shm_buf_1);
    shmdt(shm_buf_2);

	return 0;
}
