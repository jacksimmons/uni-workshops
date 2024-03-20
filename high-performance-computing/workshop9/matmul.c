/*****************************************************************
Description: Matrix multiplication using simple nested for loops. 
             This is a small test which prints out the results.

Notes: The arrays are stored row major order


**************************************************************/

#include <stdlib.h>
#include <stdio.h>

int main(){

  const int N=3;       // Dimensions of matrices are NxN
  int i, j, k;         // Loop indices
  double *A, *B, *C;   // Matrices A, B and C

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

  /* Multiply matrices using nested for loops: C=AB */
  for (i=0; i<N; i++){
    for (j=0; j<N; j++){
      for (k=0; k<N; k++){
	C[j+N*i] = C[j+N*i] + A[k+N*i] * B[j+N*k];
      }
    }
  }

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
