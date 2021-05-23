// *
// *
// *  MPI code for performing parallel dense matrix-vector multiplication using 1D
// *  rowwise partitioning.
// *
// *  Created by:  Written by Cleo Austein 23148390, Robert Kigobe 24114584, Eugene Adjeidjan 
// *  May/22/2021
// *
// *

#define N 1000
#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv){
    int size, rank, total, parallelSum;
    MPI_Status status;
    MPI_Request request;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int startRankValue = N*rank/size+1;
    int endRankValue = N*(rank+1)/size;
    
    
    parallelSum = 0;
    
    total = 0;
    
    
    for (int i = startRankValue; i <= endRankValue; i++){
        //sum up values in different ranks
        parallelSum+=i;
    }

    printf("Partial sum: %d received from %d\n", parallelSum, rank);
    
    
    for(int i = 1; i <= log2(size); i++){
        int dis = (int)pow(2, i-1);
        if (rank % dis == 0){
            
            if(rank % (2*dis) != 0){ 

                int recvpid = rank - dis;
                if (recvpid >= 0 && recvpid <= (size - 1)){
                    
                    MPI_Send(&parallelSum, 1, MPI_INT, recvpid, i, MPI_COMM_WORLD);
                    printf("Rank %d sends %d to rank %d\n", rank, parallelSum, recvpid);
                    
                }
            }
            if (rank % (2*dis) == 0){
                
                int sendpid = rank + dis;
                if (sendpid >= 0 && sendpid <= (size-1 )){
                   
                    MPI_Recv(&total, 1, MPI_INT, sendpid, i, MPI_COMM_WORLD, &status);
                    printf("Rank %d recieves %d from Rank %d\n", rank, total, sendpid);
                    parallelSum = parallelSum + total;
                    printf("Rank sum at process %d is: %d\n", rank, parallelSum);
                    
                }
            }
        }}
        
        if (rank == 0){
            printf("Total prefix sum is %d\n", parallelSum);
            
        }
        MPI_Finalize();
    
}
