
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, head, i, count = 0;
    int request[20], visited[20] = {0};
    int total = 0, min, pos;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request queue: ");
    for (i = 0; i < n; i++)
        scanf("%d", &request[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Seek Sequence: %d ", head);

    while (count < n)
    {
        min = 9999;
        pos = -1;

        for (i = 0; i < n; i++)
        {
            if (!visited[i] && abs(head - request[i]) < min)
            {
                min = abs(head - request[i]);
                pos = i;
            }
        }

        visited[pos] = 1;
        total += min;
        head = request[pos];
        printf("-> %d ", head);

        count++;
    }

    printf("\nTotal Seek Operations: %d\n", total);

    return 0;
}
