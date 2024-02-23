/*****************************************************************************
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

#include <mpi.h>

/*********************************************************************
                      Function propotypes
**********************************************************************/

void write_to_file(const char *filename, float *x, float *y, int num_pts);

/*********************************************************************
                      Main function
**********************************************************************/

int main(int argc, char **argv){

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
  const int N=7560;
 
  /* Arrays to hold values of x and y */
  // Only used on parent process.
  float x[N], y[N];

  /* Parameter t used in the parametric equations */
  float t;

  // a) Initialise MPI
  int init_code = MPI_Init(&argc, &argv);
  if (init_code != MPI_SUCCESS)
  {
     printf("Failed to initialise MPI.\n");
     return init_code;
  }

  // b) Get the communicator size, and store it in comm_size
  int comm_size;
  int comm_size_code = MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  if (comm_size_code != MPI_SUCCESS)
  {
     printf("Failed to get comm size.\n");
     return comm_size_code;
  }

  // Get the current process rank, and store it in process_rank
  int process_rank;
  int process_rank_code = MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  if (process_rank_code != MPI_SUCCESS)
  {
     printf("Failed to get process rank.\n");
     return process_rank_code;
  }

  // c) Get num points each MPI process needs to calculate
  // ! N % comm_size == 0 is necessary for this to work.
  if (N % comm_size != 0)
  {
     printf("Invalid number of processes.\n");
     return 1;
  }

  int n = N / comm_size;

  // d) Dynamically alocate point arrays 
  float *x_local;
  float *y_local;

  if (!(x_local = malloc(sizeof(float) * n)))
  {
     printf("Failed to allocate memory for x_local.\n");
     return 1;
  }

  if (!(y_local = malloc(sizeof(float) * n)))
  {
     printf("Failed to allocate memory for y_local.\n");
     return 1;
  }

  // e) Change loop iterator to [0, num_points)
  // f) Change t calculation
  // g) Replace old arrays with x_local and y_local

  /* Calculate values for x and y by looping over the parameter t */
  for (int i=0; i<n; i++){
    /* Enforce floating point division */
    t = 2.0*PI * (float)(i + process_rank * n) / (float) N;
    x_local[i] = A * sin( omega_x*t + delta_x );
    y_local[i] = B * sin( omega_y*t + delta_y );
  }

  // h) Gather calculations on the parent process
  MPI_Gather(x_local, n, MPI_FLOAT, x, n, MPI_FLOAT, 0, MPI_COMM_WORLD);
  MPI_Gather(y_local, n, MPI_FLOAT, y, n, MPI_FLOAT, 0, MPI_COMM_WORLD);

  if (process_rank == 0)
  {
     /* Write the results to a text file called output.dat */
     write_to_file("output.dat", x, y, N);
  }
  
  // d) Free up memory
  free(x_local);
  free(y_local);

  // a) Finalise MPI 
  MPI_Finalize();

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
