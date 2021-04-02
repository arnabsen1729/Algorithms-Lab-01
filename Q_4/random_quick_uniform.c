#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void mySwap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high, int *cnt)
{
    int pivot = arr[high];
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

int randomized_partition(int *arr, int initial, int final, int *count)
{
    int i = rand() % (final - initial) + initial;
    mySwap(&arr[final], &arr[i]);
    return partition(arr, initial, final, count);
}

void quickSort(int *arr, int initial, int final, int *count)
{
    if (initial < final)
    {
        int pos_of_pivot = randomized_partition(arr, initial, final, count);
        quickSort(arr, initial, pos_of_pivot, count);
        quickSort(arr, pos_of_pivot + 1, final, count);
    }
}

int checkForCorrectness(int *arr, int n)
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

void getArray(int *arr, int n)
{

    FILE *fin = fopen("./UniformDst.txt", "r");

    int temp = 0;
    fscanf(fin, "%d\n", &temp);
    for (int i = 0; i < n; i++)
    {
        int skip = rand() % 5;

        for (int j = 0; j < skip; j++)
            fscanf(fin, "%d\n", &temp);

        fscanf(fin, "%d\n", &temp);

        arr[i] = temp;
    }

    fclose(fin);
}

/* Driver code */
int main()
{
    int n = 2;
    int power = 11;
    int iterations = 20;

    FILE *fout = fopen("RQS_uniform_comparisons.txt", "w");

    for (int i = 0; i < power; i++)
    {

        long total_cnt = 0;
        float total_time = 0;

        for (int j = 0; j < iterations; j++)
        {
            int *arr = (int *)malloc(n * sizeof(int));
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
        fprintf(fout, "Size: %d, Avg. time: %0.4f, Avg. comparisons: %ld\n", n, avg_time, avg_count);
        n *= 2;
    }
    return 0;
}
