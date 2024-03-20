/*****************************************************************
Description: Matrix multiplication using simple nested for loops. 
             This is a large problem for performance tests

Notes: The arrays are stored row major order


**************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[]){

  int N;               // Dimensions of matrices are NxN
  int i, j, k;         // Loop indices
  double *A, *B, *C;   // Matrices A, B and C

  double start_time, end_time; // Timers

  /* Set the matrix size from the first command line argument */
  if (argc == 2 ){
    N =  atoi(argv[1]);
    printf("Matrix size: N= %d\n", N);
  } else {
    printf("One argument is required (matrix size N)\n");
    exit(8);
  }

  /* Allocate memory to store the matrices */
  A = (double *) malloc(N*N*sizeof(double));
  B = (double *) malloc(N*N*sizeof(double));
  C = (double *) malloc(N*N*sizeof(double));

  /* Initialise matrices A, B and C */
#pragma omp parallel for default(shared)
  for (i=0; i<N; i++){
    for (j=0; j<N; j++){
      A[j+N*i] = (double) j+N*i;
      B[j+N*i] = (double) j+1;
      C[j+N*i] = 0.0;
    }
  }

  /* Multiply matrices using nested for loops: C=AB */
  start_time = omp_get_wtime();
#pragma omp parallel for default(shared)
  for (i=0; i<N; i++){
    for (j=0; j<N; j++){
      for (k=0; k<N; k++){
	C[j+N*i] = C[j+N*i] + A[k+N*i] * B[j+N*k];
      }
    }
  }
  end_time=omp_get_wtime();

  printf("Time for matmul: %g\n", end_time-start_time);

  /* Calculate flops based on 2N^3 operations */
  double flops = 2.0 * pow((double) N,3) / (end_time-start_time);
  printf("Flops: %g GFlops\n", flops/1.0e9);

  /* Print out a value as a check */
  printf("C[100]: %g\n", C[100]);

  /* Free the memory used to store the arrays */
  free(A);
  free(B);
  free(C);

  return 0;
}
