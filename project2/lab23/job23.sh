#!/bin/bash 
#SBATCH -J MVM 
#SBATCH --ntasks 8
#SBATCH --nodes 2 
#SBATCH --tasks-per-node 4 
#SBATCH --mem-per-cpu 2GB 
#SBATCH --partition partition 
#SBATCH --account=students 

cd $SLURM_SUBMIT_DIR
module load openmpi
mpirun --mca opal_warn_on_missing_libcuda 0 -np 8 ./2D_Mat_Vec
