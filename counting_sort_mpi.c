#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 1000000
#define ROOT 0

int a[N], b[N], c[N];

int main(int argc, char **argv) {
  int i, rank, num_procs;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  // Initialize arrays
  if (rank == ROOT) {
    for (i = 0; i < N; i++) {
      a[i] = rand() % N;
      c[i] = 0;
    }
  }

  double start = MPI_Wtime();

  // Count elements
  int chunk_size = N / num_procs;
  int start_index = rank * chunk_size;
  int end_index = start_index + chunk_size - 1;
  for (i = start_index; i <= end_index; i++) {
    c[a[i]]++;
  }

  // Reduce count arrays
  int recv_counts[num_procs], displs[num_procs];
  for (i = 0; i < num_procs; i++) {
    recv_counts[i] = chunk_size;
    displs[i] = i * chunk_size;
  }
  MPI_Reduce_scatter(c, c, recv_counts, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

  // Cumulative sum
  if (rank == ROOT) {
    for (i = 1; i < N; i++) {
      c[i] += c[i - 1];
    }
  }

  // Scatter sorted elements
  MPI_Scatterv(a, recv_counts, displs, MPI_INT, a, chunk_size, MPI_INT, ROOT, MPI_COMM_WORLD);

  // Sort elements
  for (i = chunk_size - 1; i >= 0; i--) {
    b[--c[a[i]]] = a[i];
  }

  // Gather sorted arrays
  MPI_Gatherv(b, chunk_size, MPI_INT, b, recv_counts, displs, MPI_INT, ROOT, MPI_COMM_WORLD);

  double end = MPI_Wtime();

  if (rank == ROOT) {
    printf("Time taken: %f\n", end - start);
  }

  MPI_Finalize();
  return 0;
}

