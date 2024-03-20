#!/bin/bash
# Number of nodes requied
#SBATCH --nodes=1
# Number of tasks per node
#SBATCH --ntasks-per-node=1
# Number of CPUs per task
#SBATCH --cpus-per-task=16
# Maximum time the job will run for (HH:MM:SS)
#SBATCH --time=5:00
# Name of the job
#SBATCH --job-name=Hello_OpenMP
# Queue for the job to run in: training
#SBATCH -p training 
# Specify the account code and reservation
#SBATCH -A Research_Project-IscaTraining

# Unload all exisiting modules 
module purge
# Load the Intel Cluster Toolkit module used to compile the program
module load intel/2021b

# Pin threads to cores
export KMP_AFFINITY=compact

# Set the number of OpenMP threads
for threads in 2 4 8 12 16; do
    export OMP_NUM_THREADS=${threads}
    echo "Running with threads= ${OMP_NUM_THREADS}"
    ./dgemm_big 8000
    echo
done

# End of file
