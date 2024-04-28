#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

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

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int n = 1000; // Size of the array
    int* data = (int*)malloc(n * sizeof(int));

    // Initialize data with random integers
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < n; ++i) {
        data[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }

    double start_time = MPI_Wtime(); // Record start time

    int chunkSize = n / size;
    int* localData = (int*)malloc(chunkSize * sizeof(int));
    MPI_Scatter(data, chunkSize, MPI_INT, localData, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);

    quickSort(localData, 0, chunkSize - 1);

    MPI_Gather(localData, chunkSize, MPI_INT, data, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Print the sorted array
        for (int i = 0; i < n; ++i) {
            printf("%d ", data[i]);
        }
        printf("\n");

        double end_time = MPI_Wtime(); // Record end time
        printf("Execution time: %f seconds\n", end_time - start_time); // Print execution time
    }

    free(data);
    free(localData);
    MPI_Finalize();
    return 0;
}

/*

sudo apt-get update
sudo apt-get install -y mpich

mpicc -o QuickSort_MPI QuickSort_MPI.c

mpiexec -n 2 ./QuickSort_MPI

*/