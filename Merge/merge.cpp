#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long int comp = 0, s = 0;

void merge(double *a, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    double L[n1], R[n2];
    int i, j, k = 0;
    for (i = 0; i < n1; i++) {
        L[i] = a[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = a[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            comp++;
            a[k] = L[i];
            i++;
        } else {
            comp++;
            a[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        a[k] = L[i];
        k++;
        i++;
    }
    while (j < n2) {
        a[k] = R[j];
        k++;
        j++;
    }
}

void Mergesort(double *a, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        Mergesort(a, left, mid);
        Mergesort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

int main() {
    clock_t start, end;
    long int n;
    int low, high;
    double *array, time;
    int c = 1, i, k;
    FILE *fp, *fp2;
    char rfilename[30] = "ResultM.txt";
    while (c == 1 || c == 2) {
        long int n;
        comp = 0;
        s = 0;
        printf(
            "Enter (1) to sort uniformly distributed numbers.\nEnter (2) to "
            "sort normally distributed numbers.\nEnter (3) to Exit.\nChoice:");
        scanf("%d", &c);
        if (c == 1) {
            fp2 = fopen(rfilename, "a");
            fprintf(fp2, "***MERGESORT ON UNIFORM DISTRIBUTION***\n");
            fprintf(fp2, "Size\tComparisons\n");
            char opfilename[30] = "M_Sorted_UniformDst0.txt";
            char ipfilename[30] = "UniformDst0.txt";
            int j = 0;
            while (j < 10) {
                comp = 0;
                s = 0;
                fp = fopen(ipfilename, "r");
                fscanf(fp, "%d %d %ld", &low, &high, &n);
                array = (double *)malloc(n * sizeof(double));
                for (i = 0; i < n; i++) {
                    fscanf(fp, "%lf", &array[i]);
                }
                fclose(fp);

                Mergesort(array, 0, n - 1);

                fp = fopen(opfilename, "w");
                fprintf(fp, "%ld\n", n);
                for (i = 0; i < n; i++) {
                    fprintf(fp, "%d\n", (int)array[i]);
                }
                fclose(fp);
                printf("Sample Size:%ld || Number of Comparisons:%ld.\n", n,
                       comp);
                j++;
                opfilename[19]++;
                ipfilename[10]++;
                fprintf(fp2, "%ld\t%ld\n", n, comp);
            }
            fclose(fp2);
        }

        if (c == 2) {
            fp2 = fopen(rfilename, "a");
            fprintf(fp2, "***MERGESORT ON NORMAL DISTRIBUTION***\n");
            fprintf(fp2, "Size\tComparisons\n");

            char opfilename[30] = "M_Sorted_NormalDst0.txt";
            char ipfilename[30] = "NormalDst0.txt";
            int j = 0;
            while (j < 10) {
                // start=0;end=0;
                comp = 0;
                s = 0;
                fp = fopen(ipfilename, "r");
                fscanf(fp, "%ld", &n);
                array = (double *)malloc(n * sizeof(double));
                for (i = 0; i < n; i++) {
                    fscanf(fp, "%lf", &array[i]);
                }
                fclose(fp);
                // start=clock();
                Mergesort(array, 0, n - 1);
                // end=clock();
                // time=((double)end-start)/CLOCKS_PER_SEC;
                printf("Sorted Array from FILE:%s Stored in FILE:%s\n",
                       ipfilename, opfilename);
                fp = fopen(opfilename, "w");
                fprintf(fp, "%ld\n", n);
                for (i = 0; i < n; i++) {
                    fprintf(fp, "%lf\n", array[i]);
                }
                fclose(fp);
                printf("Sample Size:%ld || Number of comparisons:%ld.\n", n,
                       comp);
                // printf("Time taken to sort %ld numbers:%lf
                // seconds.\n",n,time);
                ipfilename[9]++;
                opfilename[18]++;
                j++;
                fprintf(fp2, "%ld\t%ld\n", n, comp);
            }
            fclose(fp2);
        }
    }
}
