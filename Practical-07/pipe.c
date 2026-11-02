
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int p1[2], p2[2];
    char msg[100], reply[100];

    pipe(p1);
    pipe(p2);

    if (fork() == 0)
    {
        close(p1[1]);
        close(p2[0]);

        read(p1[0], msg, sizeof(msg));
        printf("Child received: %s\n", msg);

        strcpy(reply, "Hello Parent");

        write(p2[1], reply, strlen(reply) + 1);

        close(p1[0]);
        close(p2[1]);
    }
    else
    {
        close(p1[0]);
        close(p2[1]);

        strcpy(msg, "Hello Child");

        write(p1[1], msg, strlen(msg) + 1);

        read(p2[0], reply, sizeof(reply));
        printf("Parent received: %s\n", reply);

        close(p1[1]);
        close(p2[0]);

        wait(NULL);
    }

    return 0;
}
