#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int uniformGenerator(int hi, int lo) {
    int range = hi - lo + 1;
    double frac = rand() / (1.0 + RAND_MAX);
    return (int)(frac * range + lo);
}

// void printHistogram(FILE *fp, int n, int low, int high, int *arr, int scale,
//                     int vscale) {
//     int *myNew, range, i, j;
//     range = high - low + 1;
//     myNew = (int *)calloc((range / scale), sizeof(int));
//     for (i = 0; i < n; i++) {
//         // printf("Number: %d, POsition: %d\n", arr[i], (arr[i] - low) /
//         scale); myNew[(arr[i] - low) / scale]++;
//     }
//     int mx = 0, pos = -1;
//     int mi = INT_MAX;
//     for (int i = 0; i < range / scale; i++) {
//         myNew[i] /= vscale;
//     }
//     for (i = 0; i < range / scale; i++) {
//         if (myNew[i] > mx) {
//             mx = myNew[i];
//             pos = i;
//         }
//         if (myNew[i] < mi) {
//             mi = myNew[i];
//         }
//     }
//     while (myNew[pos] != 0) {
//         for (i = 0; i < range / scale; i++) {
//             if (myNew[i] >= myNew[pos]) {
//                 printf("* ");
//             } else {
//                 printf("  ");
//             }
//             printf("  ");
//         }
//         myNew[pos] -= 1;
//         printf("\n");
//     }
//     for (i = 0; i < range / scale; i++) {
//         printf("%d  ", (i + 1));
//         fprintf(fp, "%d  ", (i + 1));
//         if (i <= 8) {
//             printf(" ");
//             // fprintf(fp, " ");
//         }
//     }
//     printf("\n");
//     fprintf(fp, "\n");
// }

int main() {
    int n, low, high, scale, vscale;
    double sum, avg;
    char filename[40] = "UniformDst.txt";

    srand(time(0));

    low = 1;
    high = 200;
    n = 100000;
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
    for (int i = 0; i < n; i++) {
        arr[i] = uniformGenerator(high, low);
        sum += arr[i];
        fprintf(fp, "%d\n", arr[i]);
        // printf("%d\n", arr[i]);
    }

    // printHistogram(fp, n, low, high, arr, scale, vscale);
    return 0;
}
