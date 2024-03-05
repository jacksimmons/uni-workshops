/*****************************************************************************
(Modified by me)

4) I would parallelise the inner loop, because it has a longer processing
time. N_POINTS >> N_CURVES too, so parallelising the inner loop will lead to
more threads being used at once. (Parallelising the outer loop would lead toonly 4 threads).

5) You can use collapse with these loops.

Results checked and match serial version.


Purpose: Program to generate Lissajous curves for ECM3446/ECMM461 workshop 2
         This version generates multiple curves and writes each curve to a 
         different file output_N.dat (where N is an integer index)

Notes: Notation follows https://mathworld.wolfram.com/LissajousCurve.html

       Compile with: gcc -o lissajou -std=c99 lissajous.c -lm


*****************************************************************************/

/*********************************************************************
                     Include header files 
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
/*********************************************************************
                      Function propotypes
**********************************************************************/

void write_to_file(const char *filename, float *x, float *y, int num_pts);

/*********************************************************************
                      Main function
**********************************************************************/

int main(){
  
  /* Define the constant pi */
  const float PI=3.14159265358979323846;

  /* Number of curves to calculate. Using a #define allows the arrays to
     be initialised here */
#define N_CURVES 4

  /* Define parameters of the Lissajous curve as constants*/
  const float A[N_CURVES]      ={1.0,    1.0,    1.0,    1.0};
  const float B[N_CURVES]      ={1.0,    1.0,    1.0,    1.0};
  const float omega_x[N_CURVES]={1.0,    3.0,    3.0,    5.0};
  const float omega_y[N_CURVES]={2.0,    2.0,    4.0,    4.0};
  const float delta_x[N_CURVES]={PI/2.0, PI/2.0, PI/4.0, PI/4.0};
  const float delta_y[N_CURVES]={0.0,    0.0,    0.0,    0.0};

  /* Number of (x,y) points to calculate */
  const int N_POINTS=10000;
  
  /* Arrays to hold values of x and y */
  float x[N_CURVES][N_POINTS], y[N_CURVES][N_POINTS];
  
  /* Parameter t used in the parametric equations */
  float t;

  /* Calculate values for x and y by looping over the parameter t */
  #pragma omp parallel for collapse(2) private(t)
  for (int curve=0; curve<N_CURVES; curve++){
    for (int i=0; i<N_POINTS; i++){
      /* Convert i and N to floats so we do floating point division */
      t = 2.0*PI * (float) i / (float) N_POINTS;
      x[curve][i] = A[curve] * sin( omega_x[curve]*t + delta_x[curve] );
      y[curve][i] = B[curve] * sin( omega_y[curve]*t + delta_y[curve] );
    }
  }
  
  /* Write the results to a text file called output_N.dat
     where N is the index of the curve we are writing out */
  {
    char filename[20];       /* The name of the file to write to */
    const char file_prefix[]="output_"; /* Start of the filename*/
    const char file_suffix[]=".dat";    /* End of the filename*/
    
    /* Loop over all the curves we need to write out*/
    // Cannot parallelise (IO)
    for (int curve=0; curve<N_CURVES; curve++){
      /* Generate the filename */
      sprintf(filename, "%s%d%s", file_prefix, curve, file_suffix );
      /* x and y are 2D arrays so pass a pointer to the curve we want to output */
      write_to_file(filename, &x[curve][0], &y[curve][0], N_POINTS);
    }
  }

  return 0;
}

/*********************************************************************

Function: write_to_file

Purpose: write x and y values to a text file in two column format 

Arguments: const char *filename (filename to write to)
           float *x (array of x values)
           float *x (array of y values)
           int num_pts (number of points to write out)

Returns: void

**********************************************************************/

void write_to_file(const char *filename, float *x, float *y, int num_pts){

  /* Open the file for writing */
  FILE *outfile;
  outfile = fopen(filename, "w");

  /* If the file could not be opened then the pointer to it will be NULL */
  if (outfile == NULL){
    printf("ERROR: could not open file %s\n", filename);
    exit(8);
  }

  /* Loop through x and y arrays writing out the values to the file */
  for (int i=0; i<num_pts; i++){
    fprintf(outfile, "%f %f\n", x[i], y[i]);
  }
  fclose(outfile);

}

/* End of file ******************************************************/
