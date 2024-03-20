/*****************************************************************
Description: Matrix multiplication using DGEMM
             This is a small test which prints out the results.

Notes: The arrays are stored row major order


**************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <cblas.h>

int main(){

  const int N=3;       // Dimensions of matrices are NxN
  int i, j;            // Loop indices
  double *A, *B, *C;   // Matrices A, B and C
  
  /* alpha and beta coefficients in DGEMM calculation */
  const double alpha=1.0;
  const double beta=0.0;

  /* Allocate memory to store the matrices */
  A = (double *) malloc(N*N*sizeof(double));
  B = (double *) malloc(N*N*sizeof(double));
  C = (double *) malloc(N*N*sizeof(double));

  /* Initialise matrices A, B and C */
  for (i=0; i<N; i++){
    for (j=0; j<N; j++){
      A[j+N*i] = (double) j+N*i;
      B[j+N*i] = (double) j+1;
      C[j+N*i] = 0.0;
    }
  }

  /* Call DGEMM to multiply the arrays: C=AB */
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
	      N, N, N, alpha, A, N, B, N, beta, C, N);

  /* Print out arrays to check the results */
  printf("Matrix A:\n");
  for (i=0; i<N; i++){
    for(j=0; j<N; j++){
      printf("%3g ", A[j+N*i]);
    }
    printf("\n");
  }

  printf("Matrix B:\n");
  for (i=0; i<N; i++){
    for(j=0; j<N; j++){
      printf("%3g ", B[j+N*i]);
    }
    printf("\n");
  }

  printf("Matrix C:\n");
  for (i=0; i<N; i++){
    for(j=0; j<N; j++){
      printf("%3g ", C[j+N*i]);
    }
    printf("\n");
  }

  /* Free the memory used to store the arrays */
  free(A);
  free(B);
  free(C);

  return 0;
}
