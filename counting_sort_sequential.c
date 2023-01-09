#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000

int a[N], b[N], c[N];

int main() {
  int i;
  clock_t start, end;
  double cpu_time_used;

  // Initialize arrays
  for (i = 0; i < N; i++) {
    a[i] = rand() % N;
    c[i] = 0;
  }
  
  start = clock();

  // Count elements
  for (i = 0; i < N; i++) {
    c[a[i]]++;
  }

  // Cumulative sum
  for (i = 1; i < N; i++) {
    c[i] += c[i - 1];
  }

  // Sort elements
  for (i = N - 1; i >= 0; i--) {
    b[--c[a[i]]] = a[i];
  }
  
  end = clock();
  
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Elapsed time: %f seconds\n", cpu_time_used);

  return 0;
}

