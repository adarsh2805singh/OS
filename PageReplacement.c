#include <stdio.h>

#define MAX 50

int search(int f[], int n, int key)
{
    for (int i = 0; i < n; i++)
        if (f[i] == key)
            return 1;
    return 0;
}

/* FIFO */
void fifo(int p[], int n, int m)
{
    int f[MAX], i, j, k = 0, faults = 0;

    for (i = 0; i < m; i++) f[i] = -1;

    printf("\nFIFO:\n");

    for (i = 0; i < n; i++)
    {
        if (!search(f, m, p[i]))
        {
            f[k] = p[i];
            k = (k + 1) % m;
            faults++;
        }

        for (j = 0; j < m; j++)
            printf("%d ", f[j]);
        printf("\n");
    }

    printf("Page Faults = %d\n", faults);
}

/* LRU */
void lru(int p[], int n, int m)
{
    int f[MAX], time[MAX], i, j, pos, min, cnt = 0, faults = 0;

    for (i = 0; i < m; i++)
        f[i] = time[i] = -1;

    printf("\nLRU:\n");

    for (i = 0; i < n; i++)
    {
        if (search(f, m, p[i]))
        {
            for (j = 0; j < m; j++)
                if (f[j] == p[i])
                    time[j] = ++cnt;
        }
        else
        {
            min = time[0], pos = 0;

            for (j = 1; j < m; j++)
                if (time[j] < min)
                    min = time[j], pos = j;

            f[pos] = p[i];
            time[pos] = ++cnt;
            faults++;
        }

        for (j = 0; j < m; j++)
            printf("%d ", f[j]);
        printf("\n");
    }

    printf("Page Faults = %d\n", faults);
}

/* Optimal */
void optimal(int p[], int n, int m)
{
    int f[MAX], i, j, k, pos, far, faults = 0;

    for (i = 0; i < m; i++) f[i] = -1;

    printf("\nOptimal:\n");

    for (i = 0; i < n; i++)
    {
        if (!search(f, m, p[i]))
        {
            pos = -1;
            far = i;

            for (j = 0; j < m; j++)
            {
                for (k = i + 1; k < n; k++)
                    if (f[j] == p[k]) break;

                if (k > far)
                {
                    far = k;
                    pos = j;
                }
            }

            if (pos == -1) pos = 0;

            f[pos] = p[i];
            faults++;
        }

        for (j = 0; j < m; j++)
            printf("%d ", f[j]);
        printf("\n");
    }

    printf("Page Faults = %d\n", faults);
}

int main()
{
    int p[MAX], n, m, i;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter pages: ");
    for (i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("Enter frame size: ");
    scanf("%d", &m);

    fifo(p, n, m);
    lru(p, n, m);
    optimal(p, n, m);

    return 0;
}
