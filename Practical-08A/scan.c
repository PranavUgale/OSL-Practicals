
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, head, size, i, j, temp;
    int request[20], total = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request queue: ");
    for (i = 0; i < n; i++)
        scanf("%d", &request[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &size);

    // Sort requests
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            if (request[i] > request[j])
            {
                temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }

    printf("Seek Sequence: %d ", head);

    // Move towards higher cylinder numbers
    for (i = 0; i < n; i++)
    {
        if (request[i] >= head)
        {
            total += abs(head - request[i]);
            head = request[i];
            printf("-> %d ", head);
        }
    }

    // Go to end of disk
    total += abs(head - (size - 1));
    head = size - 1;
    printf("-> %d ", head);

    // Reverse direction
    for (i = n - 1; i >= 0; i--)
    {
        if (request[i] < head && request[i] < size)
        {
            total += abs(head - request[i]);
            head = request[i];
            printf("-> %d ", head);
        }
    }

    printf("\nTotal Seek Operations: %d\n", total);

    return 0;
}
