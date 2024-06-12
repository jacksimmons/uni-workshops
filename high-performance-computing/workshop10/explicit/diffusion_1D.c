/*******************************************************************************
1D diffusion solver with explicit time stepping

Purpose: solve the 1D diffusion equation using explicit time stepping


*******************************************************************************/

#include <stdio.h>
#include <math.h>

int main(){

  // Grid properties
  const int NX=2000;   // Number of points
  const double xmin=0.0; // Minimum x value
  const double xmax=1.0; // Maximum x value

  // Parameters for the Gaussian initial conditions
  const double x0=0.5;
  const double sigmax=0.1;

  // Boundary conditions
  const double bval_left=0.0;
  const double bval_right=0.0;

  // Diffusivity
  const double K=1.0;

  // Required end time of the calculation
  const double end_time=0.01;

  // Arrays to store variables. These have NX+2 elements
  // to allow boundary values to be stored at both ends
  double x[NX+2];          // Grid point values
  double u[NX+2];          // Array of u values
  double dudt[NX+2];       // Rate of change of u
  
  // Calculate distance between points
  double dx = (xmax-xmin) / ( (double) NX);

  // Calculate a stable time step
  const double nu = 0.501;
  double dt = nu * (dx*dx)/K;

  // Record number of time steps taken
  int n_steps;

  // Current time
  double t;

  // Report information about the calculation
  printf("Grid spacing      = %g\n", dx);
  printf("Time step         = %g\n", dt);
  printf("End time          = %g\n", end_time);

  // Set up Gaussian initial conditions
  for (int i=0; i<NX+2; i++){
    // Place x points in the middle of the cell
    x[i]          = ( (double) i - 0.5) * dx;
    double x2      = (x[i]-x0) * (x[i]-x0);
    double sigmax2 = sigmax * sigmax;
    u[i]          = exp(-x2/(2.0*sigmax2));
  }

  // Apply boundary conditions at u[0] and u[NX+1]
  // These will not be modified
    u[0]    = bval_left;
    u[NX+1] = bval_right;
  
  // Write array of initial u values out to file
  FILE *initialfile;
  initialfile = fopen("initial.dat", "w");
  for (int i=0; i<NX+2; i++){
      fprintf(initialfile, "%g %g \n", x[i], u[i]);
    }
  fclose(initialfile);

  // Update solution by looping over time steps
  n_steps=0; t=0.0;               // Zero step counter and current time
  double tolerance=pow(2,-51);    // Define a tolerance for checking the end time
  // Loop until we reach the end time:
  while ( (end_time-t) > tolerance ){

    // Calculate rate of change of u using leftward difference
    // Loop over points in the domain but not boundary values
    for (int i=1; i<NX+1; i++){
      dudt[i] = K * (u[i+1] - 2.0*u[i] + u[i-1]) / (dx*dx);
    }

    // Update u from t to t+dt
    // Loop over points in the domain but not boundary values
    for	(int i=1; i<NX+1; i++){
      u[i] = u[i] + dudt[i] * dt;
    }

    n_steps++;
    t+=dt;

  }
  printf("Calculation finished after %d time steps\n", n_steps);

  // Write array of final u values out to file
  FILE *finalfile;
  finalfile = fopen("final.dat", "w");
  for (int i=0; i<NX+2; i++){
      fprintf(finalfile, "%g %g \n", x[i], u[i]);
    }
  fclose(finalfile);

  return 0;
}
