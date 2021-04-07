#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> //for true keyword

// all position should be given according to zero indexed array
void insertion_sort(double arr[], int initial, int final)
{
    for (int i = initial; i <= final; i++)
    {
        double value = arr[i];
        int pos = i - 1;
        while (pos >= initial && arr[pos] > value)
        {
            arr[pos + 1] = arr[pos];
            pos--;
        }
        arr[pos + 1] = value;
    }
}

// all position should be given according to zero indexed array
double give_median(double arr[], int initial, int final)
{
    insertion_sort(arr, initial, final);
    int mid = (initial + final) / 2;
    return arr[mid];
}

//give arr_size as sizeof(arr)/sizeof(int)
double median_of_median(double arr[], int arr_size, int divide_size)
{
    if (arr_size < divide_size)
    {
        double median = give_median(arr, 0, arr_size - 1);
        return median;
    }

    int no_full_group = arr_size / divide_size;
    int elements_in_last = arr_size % divide_size;

    int next_arr_size;

    if (elements_in_last == 0)
        next_arr_size = no_full_group;
    else
        next_arr_size = no_full_group + 1;

    double next_arr[next_arr_size];

    for (int i = 0; i < next_arr_size; i++)
    {
        if (i == next_arr_size - 1)
            next_arr[i] = give_median(arr, divide_size * i, arr_size - 1);
        else
            next_arr[i] = give_median(arr, divide_size * i, divide_size * (i + 1) - 1);
    }

    return median_of_median(next_arr, next_arr_size, divide_size);
}

void swap(double *a, double *b)
{
    double c = *a;
    *a = *b;
    *b = c;
}

int partition(double arr[], int low, int high)
{
    double pivot = arr[high];
    int i = low - 1;

    for (int curr = low; curr <= high; curr++)
    {
        if (arr[curr] < pivot)
        {
            i++;
            swap(&arr[i], &arr[curr]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

int findPartition(double *arr, int arr_size, int divide_size)
{
    double val = median_of_median(arr, arr_size, divide_size);
    // printf("Val: %lf\n", val);

    for (int i = 0; i < arr_size; i++)
        if (arr[i] == val)
        {
            swap(&arr[arr_size - 1], &arr[i]);
            return partition(arr, 0, arr_size - 1);
        }
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

int main()
{
    srand(time(0));

    const int max_arr_size = 1000;

    int divide_size = 5;
    int num_iter = 10;
    int part_size;
    float avg_part_size;

    FILE *fout = fopen("mom_normal_obs.txt", "w");
    // fprintf(fout, "arr_size,avg_partition_size\n");

    for (int arr_size = 100; arr_size <= max_arr_size; arr_size += 100)
    {
        double arr[arr_size];
        avg_part_size = 0;

        for (int i = 0; i < num_iter; i++)
        {
            getArray(arr, arr_size);

            part_size = findPartition(arr, arr_size, divide_size);
            // printf("Part size: %d\n", part_size);

            avg_part_size += part_size;
        }

        avg_part_size = avg_part_size / num_iter;

        printf("array_size: %d avg_part_size: %f \n", arr_size, avg_part_size);
        fprintf(fout, "Avg. size: %d, Avg. part size: %f\n", arr_size, avg_part_size);
    }

    fclose(fout);
    return 0;
}