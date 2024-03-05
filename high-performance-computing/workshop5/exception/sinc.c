/*****************************************************************************
Purpose: Program to calculate the sinc function for ECM3446/ECMM461 workshop 5

Notes: Compile with: gcc -o sinc sinc.c -lm


*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

  const float PI=3.14159265358979323846;   /* Define the constant pi */
  const int N=1000;      // Number of values to calculate
  const float range=5.0; // Calculate values between -range*pi:range*pi
  float x;               // Argument of the sinc function
  float y;               // Value of sinc(x) 
  int i;                 // Loop index
  FILE *outfile;         // Output file
  const char filename[] = "sinc.dat"; // Name of output file

  /* Open a file to write to */ 
  outfile = fopen(filename, "w");
  
  /* If the file could not be opened then the pointer to it will be NULL */
  if (outfile == NULL){
    printf("ERROR: could not open file %s\n", filename);
    exit(8);
  }

  /* Calculate values of x and y writing them out as we go */ 
  for (i=0; i<N; i++){
    x = range * PI * ( (float) (i-N/2) ) / ( (float) (N/2) );
    
    if (x == 0)
      y = 1;
    else
	  y = sin(x) / x;

    /* Report when a NaN is generated */ 
    if (isnan(y)){
      printf("NaN generated: i=%d, x=%f\n", i, x);
    }
    
    /* Write values of x and y to the output file */
    fprintf(outfile, "%f, %f\n", x, y);
  }

  /* Close the output file */
  fclose(outfile);

  return 0;

}
