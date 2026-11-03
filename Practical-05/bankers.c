#include <stdio.h>

int main()
{
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[10][10], max[10][10], avail[10];
    int need[10][10], finish[10] = {0}, safe[10];

    printf("Enter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    }

    printf("Enter Maximum Matrix:\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }

    printf("Enter Available Resources:\n");
    for(int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }

    int count = 0;

    while(count < n)
    {
        int found = 0;

        for(int i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int j;

                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > avail[j])
                        break;
                }

                if(j == m)
                {
                    for(int k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
        {
            printf("System is not in Safe State\n");
            return 0;
        }
    }

    printf("System is in Safe State\n");
    printf("Safe Sequence: ");

    for(int i = 0; i < n; i++)
        printf("P%d ", safe[i]);

    printf("\n");

    return 0;
}