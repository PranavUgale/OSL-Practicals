#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int fd1, fd2;
    char msg[100], reply[100];

    unlink("fifo1");
    unlink("fifo2");

    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    if (fork() == 0)
    {
        fd1 = open("fifo1", O_RDONLY);
        read(fd1, msg, sizeof(msg));
        close(fd1);

        printf("Child received: %s\n", msg);

        strcpy(reply, "Hello Parent");

        fd2 = open("fifo2", O_WRONLY);
        write(fd2, reply, strlen(reply) + 1);
        close(fd2);
    }
    else
    {
        strcpy(msg, "Hello Child");

        fd1 = open("fifo1", O_WRONLY);
        write(fd1, msg, strlen(msg) + 1);
        close(fd1);

        fd2 = open("fifo2", O_RDONLY);
        read(fd2, reply, sizeof(reply));
        close(fd2);

        printf("Parent received: %s\n", reply);

        wait(NULL);
    }

    unlink("fifo1");
    unlink("fifo2");

    return 0;
}