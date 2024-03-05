/*******************************************************************************
5: Question 5

1D advection example program which advects a Gaussian u(x) at a fixed velocity



Outputs: initial.dat - inital values of u(x) 
         final.dat   - final values of u(x)

         The output files have two columns: x, u

         Compile with: gcc -o advection1D -std=c99 advection1D.c -lm

Notes: The time step is calculated using the CFL condition

********************************************************************************/

/*********************************************************************
                     Include header files 
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*********************************************************************
                      Function propotypes
**********************************************************************/

void write_to_file(const char *filename, float *x, float *u, int num_pts);

/*********************************************************************
                      Main function
**********************************************************************/

int main(){

  /* Grid properties */
  const int NX=10000;   // Number of points
  const float xmin=0.0; // Minimum x value
  const float xmax=1.0; // Maximum x value

  /* Parameters for the Gaussian initial conditions */
  const float x0=0.3;                // Centre
  const float sigmax=0.05;           // Width
  const float sigmax2=sigmax*sigmax; // Need sigma^2 to calculate Gaussian

  /* Boundary conditions */
  const float bval_left=0.0;   // Boundary condition at left edge
  const float bval_right=0.0;  // Boundary condition at right edge

  /* Time stepping parameters */
  const float CFL=1.01f;   // CFL (Courant) number 
  const int nsteps=5000; // Number of time steps

  /* Velocity */
  const float velx=0.01; // Velocity in x direction

  /* Arrays to store variables. These have NX+2 elements
     to allow boundary values to be stored at both ends */
  float x[NX+2];          // Grid point values
  float u[NX+2];          // Array of u values
  float dudt[NX+2];       // Rate of change of u
  
  /* Calculate distance between points */
  float dx = (xmax-xmin) / ( (float) NX);

  /* Calculate time step using the CFL condition */
  /* The fabs function gives the absolute value of a float in case velx is negative */
  float dt = CFL * ( dx / fabs(velx) );

  float x2;  // x squared (used in initial conditions set up)
  
  /*** Report information about the calculation ***/
  printf("Grid spacing      = %g\n", dx);
  printf("CFL number        = %g\n", CFL);
  printf("Time step         = %g\n", dt);
  printf("No. of time steps = %d\n", nsteps);
  printf("End time          = %g\n", dt*(float) nsteps);
  printf("Distance advected = %g\n", velx*dt*(float) nsteps);

  /*** Set up Gaussian initial conditions ***/
  for (int i=0; i<NX+2; i++){
    // Place x points in the middle of the cell
    x[i] = ( (float) i - 0.5) * dx;
    x2   = (x[i]-x0) * (x[i]-x0);
    u[i] = exp( -x2 / (2.0*sigmax2) );
  }
  
  /*** Write array of initial u values out to file ***/
  write_to_file("initial.dat", x, u, NX);
  
  /*** Update solution by looping over time steps ***/
  for (int m=0; m<nsteps; m++){

    /* Apply boundary conditions at u[0] and u[NX+1] */
    u[0]    = bval_left;
    u[NX+1] = bval_right;

    /* Calculate rate of change of u using leftward difference
       Loop over points in the domain but not boundary values */
    for (int i=1; i<NX+1; i++){
      dudt[i] = -velx * (u[i] - u[i-1]) / dx;
    }

    /* Update u from time t to t+dt
       Loop over points in the domain but not boundary values */
    for	(int i=1; i<NX+1; i++){
      u[i] = u[i] + dudt[i] * dt;
    }
    
  } /* End loop over time steps */

  /*** Write array of final u values out to file ***/
  write_to_file("final.dat", x, u, NX);

  return 0;
}

/*********************************************************************

Function: write_to_file

Purpose: write two arrays to a text file in two column format 

Arguments: const char *filename (filename to write to)
           float *x (array to write out as column 1)
           float *u (array to write out as column 2)
           int num_pts (number of points to write out)

Returns: void

**********************************************************************/

void write_to_file(const char *filename, float *x, float *u, int num_pts){

  /* Open the file for writing */
  FILE *outfile;
  outfile = fopen(filename, "w");

  /* If the file could not be opened then the pointer to it will be NULL */
  if (outfile == NULL){
    printf("ERROR: could not open file %s\n", filename);
    exit(8);
  }

  /* Loop through the arrays writing out the values to the file */
  for (int i=0; i<num_pts; i++){
    fprintf(outfile, "%f %f\n", x[i], u[i]);
  }
  fclose(outfile);

}

/* End of file ******************************************************/
