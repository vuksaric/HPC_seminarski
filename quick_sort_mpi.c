#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void QuickSort(int *array, int left, int right)
{
    int i = left, j = right;
    int tmp;
    int pivot = array[(left + right) / 2];

    /* partition */
    while (i <= j)
    {
        while (array[i] < pivot)
            i++;
        while (array[j] > pivot)
            j--;
        if (i <= j)
        {
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            i++;
            j--;
        }
    }

    /* recursion */
    if (left < j)
        QuickSort(array, left, j);
    if (i < right)
        QuickSort(array, i, right);
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 1000000;
    int *array = malloc(n * sizeof(int));
    if (rank == 0)
        for (int i = 0; i < n; i++)
            array[i] = rand();

    double tic = MPI_Wtime();
    MPI_Bcast(array, n, MPI_INT, 0, MPI_COMM_WORLD);
    QuickSort(array, 0, n - 1);
    double toc = MPI_Wtime();

    if (rank == 0)
        printf("Elapsed time: %f seconds\n", toc - tic);

    free(array);
    MPI_Finalize();
    return 0;
}
