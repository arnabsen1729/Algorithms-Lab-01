#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int uniformGenerator(int hi, int lo)
{
    int range = hi - lo + 1;
    double frac = rand() / (1.0 + RAND_MAX);
    return (int)(frac * range + lo);
}

void printHistogram(FILE *fp, int n, int low, int high, int *arr, int scale,
                    int vscale)
{
    int *new, range, i, j;
    range = high - low + 1;
    new = (int *)calloc((range / scale), sizeof(int));
    for (i = 0; i < n; i++)
    {
        // printf("Number: %d, POsition: %d\n", arr[i], (arr[i] - low) / scale);
        new[(arr[i] - low) / scale]++;
    }
    int mx = 0, pos = -1;
    int mi = INT_MAX;
    for (int i = 0; i < range / scale; i++)
    {
        new[i] /= vscale;
    }
    for (i = 0; i < range / scale; i++)
    {
        if (new[i] > mx)
        {
            mx = new[i];
            pos = i;
        }
        if (new[i] < mi)
        {
            mi = new[i];
        }
    }
    while (new[pos] != 0)
    {
        for (i = 0; i < range / scale; i++)
        {
            if (new[i] >= new[pos])
            {
                printf("* ");
            }
            else
            {
                printf("  ");
            }
            printf("  ");
        }
        new[pos] -= 1;
        printf("\n");
    }
    for (i = 0; i < range / scale; i++)
    {
        printf("%d  ", (i + 1));
        fprintf(fp, "%d  ", (i + 1));
        if (i <= 8)
        {
            printf(" ");
            // fprintf(fp, " ");
        }
    }
    printf("\n");
    fprintf(fp, "\n");
}

int main()
{
    int n, low, high, scale, vscale;
    double sum, avg;
    char filename[40] = "UniformDst.txt";

    srand(time(0));

    low = 1;
    high = 100;
    n = 5000;
    scale = 5;
    vscale = 13;
    // printf("\nEnter lower bound: ");
    // scanf("%d", &low);
    // printf("Enter upper bound: ");
    // scanf("%d", &high);
    // printf("Enter data size: ");
    // scanf("%d", &n);
    // printf("Enter scale: ");
    // scanf("%d", &scale);
    // printf("Enter file name: ");
    // scanf("%s", filename);
    printf("\n");

    int *arr = (int *)malloc(n * sizeof(int));
    FILE *fp;
    fp = fopen(filename, "w");
    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = uniformGenerator(high, low);
        sum += arr[i];
        fprintf(fp, "%d\n", arr[i]);
        // printf("%d\n", arr[i]);
    }

    printHistogram(fp, n, low, high, arr, scale, vscale);
    return 0;
}
