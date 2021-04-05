#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int nprosc, mypid,i,c=0,rdata;


	MPI_Init(&argc, &argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, &nprosc);
	MPI_Comm_rank(MPI_COMM_WORLD, &mypid);
	for (i = 1; i< 101; i++)
	{
		c = c + i + mypid * 100;
	}
	printf("Partial sum from process %d of total %d is : %d\n", mypid, nprosc, c);
	
	if (mypid == 0) {
		for (i = 1; i< 10; i++)
		{
			MPI_Recv(&rdata, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Receive %d from process %d\n", rdata, i);
			
		c = c + rdata;
		}
		printf("Total sum is %d", c);
	}
	else
														{
														MPI_Send(&c, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);	
														printf("Send %d to process 0 by process %d\n", c,mypid);
														}
																			
													MPI_Finalize();
													return 0;
}
