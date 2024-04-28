#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quickSort(int* arr, int left, int right) {
    if (left < right) {
        int pivot = arr[right]; // Choose the pivot element
        int i = left - 1;

        for (int j = left; j < right; ++j) {
            if (arr[j] < pivot) {
                i++;
                // Swap arr[i] and arr[j]
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        // Swap arr[i+1] and arr[right] (pivot)
        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;

        int partitionIndex = i + 1;

        // Recursive calls to sort the partitions
        quickSort(arr, left, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, right);
    }
}

int main() {
    const int n = 100; // Size of the array
    int* data = (int*)malloc(n * sizeof(int));

    // Initialize data with random integers
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < n; ++i) {
        data[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }

    double start_time = clock() / (double)CLOCKS_PER_SEC; // Record start time

    quickSort(data, 0, n - 1);

    double end_time = clock() / (double)CLOCKS_PER_SEC; // Record end time
    printf("Sorted array:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n");
    printf("Execution time: %f seconds\n", end_time - start_time); // Print execution time

    free(data);
    return 0;
}
