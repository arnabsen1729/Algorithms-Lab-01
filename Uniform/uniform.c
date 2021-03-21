#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
int uniformGenerator(int hi, int lo)
{
    int range = hi - lo + 1;
    double frac = rand() / (1.0 + RAND_MAX);
    return (int)(frac * range + lo);
}

void printHistogram(FILE *fp, int n, int low, int high, int *arr, int scale)
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
    while (new[pos] != mi)
    {
        for (i = 0; i < range / scale; i++)
        {
            if (new[i] >= new[pos])
            {
                printf("* ");
                fprintf(fp, "* ");
            }
            else
            {
                printf("  ");
                fprintf(fp, "  ");
            }
            printf("  ");
            fprintf(fp, "  ");
        }
        new[pos] -= 1;
        printf("\n");
        fprintf(fp, "\n");
    }
    for (i = 0; i < range / scale; i++)
    {
        printf("%d  ", (i + 1));
        fprintf(fp, "%d  ", (i + 1));
        if (i <= 8)
        {
            printf(" ");
            fprintf(fp, " ");
        }
    }
    printf("\n");
    fprintf(fp, "\n");
}

int main()
{
    int n, low, high, scale;
    double sum, avg;
    char filename[40];

    srand(time(0));

    printf("\nEnter lower bound: ");
    scanf("%d", &low);
    printf("Enter upper bound: ");
    scanf("%d", &high);
    printf("Enter data size: ");
    scanf("%d", &n);
    printf("Enter scale: ");
    scanf("%d", &scale);
    printf("Enter file name: ");
    scanf("%s", filename);
    printf("\n");

    int *arr = (int *)malloc(n * sizeof(int));
    FILE *fp;
    fp = fopen(filename, "w");

    fprintf(fp, "Low = %d\nHigh = %d\nSize = %d\nScale = %d\n\nDataset:-\n", low, high, n, scale);

    for (int i = 0; i < n; i++)
    {
        arr[i] = uniformGenerator(high, low);
        sum += arr[i];
        fprintf(fp, "%d, ", arr[i]);
        // printf("%d\n", arr[i]);
    }

    fprintf(fp, "\n\nThe histogram is generated below:- \n\n");

    printHistogram(fp, n, low, high, arr, scale);
    return 0;
}