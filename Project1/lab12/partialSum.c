#include <mpi.h>
#include <stdio.h>

//start of main program
int main(int argc, char *argv[]) {
	int nprosc, mypid,i,c=0,rdata;
	MPI_Init(&argc, &argv);
	
	
	MPI_Comm_size(MPI_COMM_WORLD, &nprosc);
	MPI_Comm_rank(MPI_COMM_WORLD, &mypid);
	
	//declare information to share			
	MPI_Status* stats[nprosc];
	MPI_Request reqs[nprosc];
							
	
	for (i = 1; i< 101; i++)
	{													c = c + i + mypid * 100;
													    }
													    printf("Partial sum from process %d of total %d is : %d\n", mypid, nprosc, c);
	MPI_Finalize();															
	return 0;	
}
