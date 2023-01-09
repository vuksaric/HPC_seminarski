#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000

int a[N], b[N], c[N];

int main() {
  int i;

  // Initialize arrays
  for (i = 0; i < N; i++) {
    a[i] = rand() % N;
    c[i] = 0;
  }

  double start = omp_get_wtime();

  // Count elements
  #pragma omp parallel for
  for (i = 0; i < N; i++) {
    #pragma omp atomic
    c[a[i]]++;
  }

  // Cumulative sum
  for (i = 1; i < N; i++) {
    c[i] += c[i - 1];
  }

  // Sort elements
  #pragma omp parallel for
  for (i = N - 1; i >= 0; i--) {
    b[--c[a[i]]] = a[i];
  }

  double end = omp_get_wtime();

  printf("Time taken: %f\n", end - start);

  return 0;
}

