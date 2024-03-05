/***********************************************************************
Description: The hybrid Hello World program for workshop 6

Purpose: demonstrate the use of hybrid MPI/OpenMP by printing a 
         Hello World message from each OpenMP thread. The thread also 
         reports the rank of the parent MPI process, the number of MPI 
         processes, the thread ID and the number of OpenMP threads, and 
         the processesor name.

Notes: compile with: mpicc -fopenmp -o hello_mpi hello_mpi.c
       run with:     sbatch run_hello_hybrid.sh


************************************************************************/

#include <stdio.h>
#include <mpi.h>
#include <omp.h>

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

  /* Get processor name */
  MPI_Get_processor_name(procName, &nameLen);

#pragma omp parallel default(shared)
  {
  /* Report rank and total number of processes and processor name */
    printf("Hello World: process %d of %d, thread %d of %d, running on %s\n", 
	   myRank, nProcs, omp_get_thread_num(), omp_get_num_threads(), procName);
  }

  /* Shut down the MPI environment*/
  MPI_Finalize();

  return 0;
}
