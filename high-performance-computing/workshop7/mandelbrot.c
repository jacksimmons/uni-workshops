/*****************************************************************************
Purpose: Calculate the Mandlebrot set for workshop 6


*****************************************************************************/

#include <stdio.h>
#include <complex.h>
#include <stdbool.h>
#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#endif

int main(){

  /* Declare variables */
  /* Loop indices for real and imaginary axes */
  int i, j;
  /* Loop index for iteration */
  int k;
  /* Maximum number of iterations */
  const int maxIter=100;

  /* Number of points on real and imaginary axes */
  const int nRe = 12000;
  const int nIm = 8000;

  /* Domain size */
  const float z_Re_min = -2.0;
  const float z_Re_max =  1.0;
  const float z_Im_min = -1.0;
  const float z_Im_max =  1.0;
  
  /* Real and imaginary components of z */
  float z_Re, z_Im;
  /* Value of Z at current iteration */
  float complex z;
  /*Value of z at iteration zero */
  float complex z0;

  /* Array to store the number of iterations at each point */
  int nIter[nRe+1][nIm+1];

  /* Flag to control whether results are written to file */
  const bool doIO = false; 

  /* Say how many threads we are using. This needs to be done from within a parallel region */ 
#ifdef _OPENMP
#pragma omp parallel
  {
    /* The single pragma means that only one thread writes this message */
#pragma omp single
    printf("Starting calculation on %d threads \n", omp_get_num_threads());
  }
#else
  printf("Starting serial calculation\n");
#endif

  /* Loop over real and imaginary axes */
#pragma omp parallel for default(shared) private(i, j, k, z_Re, z_Im, z0, z)
  for (i=0; i<nRe+1; i++){
    for (j=0; j<nIm+1; j++){
      z_Re = ( ( (float) i)/ ( (float) nRe)) * (z_Re_max - z_Re_min) + z_Re_min;
      z_Im = ( ( (float) j)/ ( (float) nIm)) * (z_Im_max - z_Im_min) + z_Im_min;
      z0 = z_Re + z_Im*I;
      z  = z0;

      /* Iterate up to a maximum number or bail out if mod(z) > 2 */
      k=0;
      while(k<maxIter){
        nIter[i][j] = k;
	if (cabs(z) > 2.0)
	  break;
	z = z*z + z0;
	k++;
      }
    }
  }
  
  /* Write out the results if doIO is true */
  if (doIO){
    printf("Writing out results\n");
    FILE *outfile;
    outfile=fopen("mandelbrot.dat","w");

    for (i=0; i<nRe+1; i++){
      for (j=0; j<nIm+1; j++){
	z_Re = ( ( (float) i)/ ( (float) nRe)) * (z_Re_max - z_Re_min) + z_Re_min;
	z_Im = ( ( (float) j)/ ( (float) nIm)) * (z_Im_max - z_Im_min) + z_Im_min;
	fprintf(outfile,"%f %f %d \n",z_Re, z_Im, nIter[i][j]);
      }
    }
    fclose(outfile);
  }
  return 0;

}
