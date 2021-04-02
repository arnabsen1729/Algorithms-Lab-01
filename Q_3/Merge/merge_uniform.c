#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void merge(int arr[], int l, int m, int r, int *cnt)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
            (*cnt)++;
        }
        else
        {
            arr[k] = R[j];
            j++;
            (*cnt)++;
        }
        k++;
    }

    /* Copying the remaining elements of L[], if there
    are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
        (*cnt)++;
    }

    /* Copying the remaining elements of R[], if there
    are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
        (*cnt)++;
    }
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r, int *cnt)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m, cnt);
        mergeSort(arr, m + 1, r, cnt);

        merge(arr, l, m, r, cnt);
    }
}

/* UTILITY FUNCTIONS */

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
    int power = 12;
    int iterations = 20;

    FILE *fout = fopen("Uniform_comparisons.txt", "w");

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
            mergeSort(arr, 0, n - 1, &cnt);
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
