#include <stdio.h>

void mySwap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int curr = low; curr <= high; curr++) {
        if (arr[curr] < pivot) {
            i++;
            mySwap(&arr[i], &arr[curr]);
        }
    }
    mySwap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low >= high) {
        return;
    }
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
}

void checkSortCorrectness(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            printf("\nSorting algo failed at index %d !!\n\n", i);
            return;
        }
    }
    printf("\nSorting algo correctness passed!!\n\n");
}

int main() {
    int arr[100];
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter the elements: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    quickSort(arr, 0, n - 1);
    printf("Elements after sorting: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    checkSortCorrectness(arr, n);
    return 0;
}
