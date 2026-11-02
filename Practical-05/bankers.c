
#include <stdio.h>

int main()
{
    int n = 5, m = 3;
    
    int alloc[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int max[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int avail[3] = {3, 3, 2};
    int need[5][3];
    int finish[5] = {0};
    int safe[5];
    int count = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    while (count < n)
    {
        int found = 0;

        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int j;

                for (j = 0; j < m; j++)
                    if (need[i][j] > avail[j])
                        break;

                if (j == m)
                {
                    for (int k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
            break;
    }

    if (count == n)
    {
        printf("System is in Safe State\n");
        printf("Safe Sequence: ");

        for (int i = 0; i < n; i++)
            printf("P%d ", safe[i]);
    }
    else
    {
        printf("System is in Unsafe State\n");
    }

    printf("\n");
    return 0;
}
