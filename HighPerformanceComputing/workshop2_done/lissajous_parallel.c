/*****************************************************************************
(Modified by me)

Q1: There are no dependencies that *prevent* it being parallelised, but there
are constant dependencies. The parameter t uses incorrect scope which may cause
a parallelised version to not work as expected.
Q2: No it cannot, as file writing is done serially (line by line).
Q3: I changed the scope of t.
t was a shared variable, when it should have been private, so I moved it inside
the for loop to make it so.


Purpose: Program to generate Lissajous curves for ECM3446/ECMM461 workshop 2

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

  /* Define parameters of the Lissajous curve as constants*/
  const float A=1.0;
  const float B=1.0;
  const float omega_x=1.0;
  const float omega_y=2.0;
  const float delta_x=PI/2.0;
  const float delta_y=0.0;

  /* Number of (x,y) points to calculate */
  int N=10000;

  /* Arrays to hold values of x and y */
  float x[N], y[N];

  /* Calculate values for x and y by looping over the parameter t */
  #pragma omp parallel for
  for (int i=0; i<N; i++){
    /* Convert i and N to floats so we do floating point division */
    float t = 2.0*PI * (float) i / (float) N; // t in loop => Private
    x[i] = A * sin( omega_x*t + delta_x );
    y[i] = B * sin( omega_y*t + delta_y );
  }

  /* Write the results to a text file called output.dat */
  /* x and y are converted to pointers because they are arrays */
  write_to_file("output.dat", x, y, N);
  
  return 0;
}

/*********************************************************************

Function: write_to_file

Purpose: write x and y values to a text file in two column format 

Arguments: const char *filename (filename to write to)
           float *x (array of x values)
           float *y (array of y values)
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
