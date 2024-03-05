/******************************************************************
Description: The Hello World program for workshop 6

Purpose: demonstrate the use of an OpenMP pragma 
         by printing "Hello World!" from each thread

Notes: compile with: gcc -fopenmp -o hello hello.c
       run with:     sbatch run_hello.sh


******************************************************************/

#include <stdio.h>
#include <omp.h>

int main(){
#pragma omp parallel
  {
    printf("Hello World from thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
  }
  return 0;
}
