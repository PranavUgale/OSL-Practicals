#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int a[] = {5, 2, 8, 1, 3};
    int i, j, temp;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child Process\n");
        printf("Child PID: %d\n", getpid());

        // Sort array in ascending order
        for (i = 0; i < 5; i++)
        {
            for (j = i + 1; j < 5; j++)
            {
                if (a[i] > a[j])
                {
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                }
            }
        }

        printf("Sorted array by Child: ");
        for (i = 0; i < 5; i++)
            printf("%d ", a[i]);

        printf("\n");
        exit(0);
    }
    else
    {
        wait(NULL);

        printf("\nParent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        // Sort array in descending order
        for (i = 0; i < 5; i++)
        {
            for (j = i + 1; j < 5; j++)
            {
                if (a[i] < a[j])
                {
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                }
            }
        }

        printf("Sorted array by Parent: ");
        for (i = 0; i < 5; i++)
            printf("%d ", a[i]);

        printf("\n");
    }

    return 0;
}