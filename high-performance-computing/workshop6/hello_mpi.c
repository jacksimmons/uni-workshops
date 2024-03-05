/***********************************************************************
Description: The MPI Hello World program for workshop 6

Purpose: demonstrate the use of MPI by printing a Hello World message
         from each MPI process. The process also reports its rank,
         the total number of MPI processes and the processor name.

Notes: compile with: mpicc -o hello_mpi hello_mpi.c
       run with:     sbatch run_hello_mpi.sh


************************************************************************/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){

  int myRank, nProcs; 
  char procName[MPI_MAX_PROCESSOR_NAME];
  int nameLen;

  /* Initialise MPI environment*/
  MPI_Init(&argc, &argv);
  /* Find the rank of this process*/
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  /* Find the total number of processes*/
  MPI_Comm_size(MPI_COMM_WORLD, &nProcs);

  /* Get processor name*/
  MPI_Get_processor_name(procName, &nameLen);

  /* Report rank and total number of processes*/
  printf("Hello World from process %d of %d running on %s\n", myRank, nProcs, procName);

  /* Shut down the MPI environment*/
  MPI_Finalize();

  return 0;
}
