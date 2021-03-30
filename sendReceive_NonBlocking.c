//This program can only be run on a processor with 2 cores

#include <stdio.h>
#include <mpi.h>





int main (int argc, char** argv)
{
	MPI_Init(NULL,NULL);
        int rank,size;

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	int totalSum = 0;
	int numbers[10] = {1,2,3,4,5,6,7,8,9,10};
	if(rank != 1)
	{
		MPI_Send(&numbers, //data being sent
			10, //count of data elements
			MPI_INT,//data type of elements
			1,//address destination
			0,//tag
			MPI_COMM_WORLD);//group of processors
	}else if(rank == 1)
	{
		MPI_Recv(&numbers,//data being sent
			10,//count of elements
			MPI_INT,//data type
			0,//source
			0,//tag
			MPI_COMM_WORLD,//communicator
			MPI_STATUS_IGNORE);//status
		for(int i=0; i<sizeof(&numbers); i++)
		{
			totalSum += numbers[i];

			
		}
		printf("Total Sum in processor %d is %d\n", rank,totalSum);
	
	}
	printf("This is a non blocking operation in processor %d of %d\n", rank,size);

	MPI_Finalize();

	return 0;
}	

	
