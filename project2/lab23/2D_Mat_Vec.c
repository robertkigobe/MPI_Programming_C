 // *
// *
// *  MPI code for performing parallel dense matrix-vector multiplication using 1D
// *  rowwise partitioning.
// *
// *  Created by:  Written by Cleo Austein 23148390, Robert Kigobe 24114584, Eugene Adjeidjan 
// *  May/22/2021
// *
// *


    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <mpi.h>
    #define SIZE 8

    int MatrixA[SIZE][SIZE], Vector[SIZE], outPut[SIZE]; int final[SIZE];
    void GenerateMatrix()
    {
    static int n=1;
    int i, j;
    for (i=0; i< SIZE; i++)
        for (j=0; j< SIZE; j++)
            MatrixA[i][j] = n++;


    }

    void GenerateVector(){;
        int i;
        for(i=0;i< SIZE;i++){
            Vector[i]=i+2;
        }
    }
    void print()
    {
        printf("\nInput Matrix ");
        for (int i = 0; i < SIZE; i++) {
            printf("\n\t|");
            for (int j = 0; j < SIZE; j++)
                printf("%2d ", MatrixA[i][j]);
            printf("|");
        }
        printf("\n\nVector\n");
        for (int i = 0; i < SIZE; i++) {
            printf("\n\t|%2d ", Vector[i]);
            printf("|");
        }
        printf("\n\nMultiplication\n");
        for (int i = 0; i < SIZE; i++) {
            printf("\n\t|%2d ", final[i]);
            printf("|");
        }
	printf("\n");
    }

    int main(int argc, char* argv[]) {
        int pid,procNum;

        int start, end;
        MPI_Init(&argc, &argv);

        MPI_Comm_size(MPI_COMM_WORLD, &procNum);
        MPI_Comm_rank(MPI_COMM_WORLD, &pid);

        start = pid* SIZE /procNum;;
        if(pid == 0) {
            GenerateMatrix();
            GenerateVector();
        }
        MPI_Bcast (Vector, SIZE, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter (MatrixA, 1, MPI_INT, MatrixA[start], 1, MPI_INT, 0, MPI_COMM_WORLD);

        outPut[start] = 0;
        outPut[start] += MatrixA[start][0]* Vector[(int)pid%SIZE];
    
        MPI_Reduce(&outPut,&final,SIZE,MPI_INT, MPI_SUM,0,MPI_COMM_WORLD);
        if (pid == 0) {
            print();
        }
        MPI_Finalize();
        return 0;
    }
