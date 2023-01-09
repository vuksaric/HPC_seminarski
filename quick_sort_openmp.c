#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

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
    {
        #pragma omp task
        QuickSort(array, left, j);
    }
    if (i < right)
    {
        #pragma omp task
        QuickSort(array, i, right);
    }
}

int main(int argc, char *argv[])
{
    int n = 1000000;
    int *array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        array[i] = rand();

    double tic = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single nowait
        QuickSort(array, 0, n - 1);
    }
    double toc = omp_get_wtime();

    printf("Elapsed time: %f seconds\n", toc - tic);
    free(array);
    return 0;
}
