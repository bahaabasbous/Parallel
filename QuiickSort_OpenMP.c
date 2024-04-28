#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void quickSort(int* arr, int left, int right);

int main() {
    const int n = 1000; // Size of the array
    int* data = (int*)malloc(sizeof(int) * n);

    // Initialize data (e.g., random values)
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        data[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }
	
	omp_set_num_threads(2);
    
	double start_time = omp_get_wtime(); // Record start time

    #pragma omp parallel
    {
        #pragma omp single nowait
        quickSort(data, 0, n - 1);
    }

    double end_time = omp_get_wtime(); // Record end time
    double execution_time = end_time - start_time; // Calculate execution time

    // Print the sorted array
    for (int i = 0; i < n; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n");

    printf("Execution time: %f seconds\n", execution_time);

    free(data);
    return 0;
}

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
        #pragma omp task
        quickSort(arr, left, partitionIndex - 1);
        #pragma omp task
        quickSort(arr, partitionIndex + 1, right);
    }
}


/*

sudo apt-get update
sudo apt-get install libomp-dev
sudo dnf install libomp-devel


g++ -o QuickSort_OpenMP QuickSort_OpenMP.c -fopenmp

./QuickSort_OpenMP

*/



