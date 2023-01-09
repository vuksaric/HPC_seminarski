#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    int n = 1000000;
    clock_t start, end;
    double cpu_time_used;
    
    int *array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        array[i] = rand();

    start = clock();
    QuickSort(array, 0, n - 1);
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", cpu_time_used);

    free(array);
    return 0;
}

