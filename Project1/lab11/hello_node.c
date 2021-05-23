#include <mpi.h>
#include <stdio.h>
int main(int argc,char** argv) {
	//the argc and argv allows the programmer to pass paramaters form the command line
	//argc stands for argument count
	//argv stands for argument vector

       
    	// Initialize the MPI environment
    	// During MPI_Init, all of MPI's global and internal variables are constructed.
     	MPI_Init(NULL, NULL);
   
    
     	// Print off a hello world message
     	int rank, size;
     	MPI_Comm_rank(MPI_COMM_WORLD, &mypid);
     	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
     	 
     	printf("Hello world from process %d of total %d !\n",mypid,nprocs);
     	 
    	//Finalize the MPI environment.
    	// No more MPI calls can be made after this one.
     	MPI_Finalize();       
     }
