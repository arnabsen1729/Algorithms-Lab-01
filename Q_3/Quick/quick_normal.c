#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void mySwap(double *a, double *b)
{
    double t = *a;
    *a = *b;
    *b = t;
}

int partition(double arr[], int low, int high, int *cnt)
{
    double pivot = arr[high];
    int i = low - 1;

    for (int curr = low; curr <= high; curr++)
    {
        if (arr[curr] < pivot)
        {
            i++;
            mySwap(&arr[i], &arr[curr]);
            (*cnt)++;
        }
    }
    mySwap(&arr[i + 1], &arr[high]);
    (*cnt)++;
    return (i + 1);
}

void quickSort(double arr[], int low, int high, int *cnt)
{
    if (low >= high)
    {
        return;
    }
    int pi = partition(arr, low, high, cnt);
    quickSort(arr, low, pi - 1, cnt);
    quickSort(arr, pi + 1, high, cnt);
}

int checkForCorrectness(double *arr, int n)
{
    int correct = 1;
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < arr[i - 1])
        {
            correct = 0;
            break;
        }
    }
    return correct;
}

void getArray(double *arr, int n)
{

    FILE *fin = fopen("./NormalDst.txt", "r");

    double temp = 0.0;
    fscanf(fin, "%lf\n", &temp);
    for (int i = 0; i < n; i++)
    {
        int skip = rand() % 5;

        for (int j = 0; j < skip; j++)
            fscanf(fin, "%lf\n", &temp);

        fscanf(fin, "%lf\n", &temp);

        arr[i] = temp;
    }

    fclose(fin);
}

/* Driver code */
int main()
{
    int n = 2;
    int power = 15;
    int iterations = 20;

    FILE *fout = fopen("Normal_comparisons.txt", "w");

    for (int i = 0; i < power; i++)
    {

        long total_cnt = 0;
        float total_time = 0;

        for (int j = 0; j < iterations; j++)
        {
            double *arr = (double *)malloc(n * sizeof(double));
            int cnt = 0;
            getArray(arr, n);

            float start_time = clock();
            quickSort(arr, 0, n - 1, &cnt);
            float end_time = clock();

            total_cnt += cnt;

            float time_taken = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
            total_time += time_taken;

            if (checkForCorrectness(arr, n))
            {
                //printf("\nNum = %d Run %d: %d comparisons, %0.4f ms", n, j + 1, cnt, time_taken);
            }
            else
            {
                printf("\nArray Not Sorted");
                break;
            }
        }
        float avg_time = total_time / iterations;
        long avg_count = total_cnt / iterations;
        //printf("\nN: %d, Avg time: %0.4f, Avg count: %ld\n", n, avg_time, avg_count);
        fprintf(fout, "%d, %0.4f, %ld\n", n, avg_time, avg_count);
        n *= 2;
    }
    return 0;
}
