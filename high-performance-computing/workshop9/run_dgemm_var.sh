#!/bin/bash
# Number of nodes requied
#SBATCH --nodes=1
# Number of tasks per node
#SBATCH --ntasks-per-node=1
# Number of CPUs per task
#SBATCH --cpus-per-task=8
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
export OMP_NUM_THREADS=8
echo "Threads: ${OMP_NUM_THREADS}"

# Run with different size matrices
for size in 4000 6000 8000 10000 12000; do
    echo "Running with size ${size}"
    ./dgemm_big ${size}
    echo
done

# End of file
