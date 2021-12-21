#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
	int rank, size;
    // initializing MPI library
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int vector_size = 1000000;
    int vector[vector_size];
    fill_n(vector, vector_size, 1);
    for (int i = 0; i < vector_size; i++){
        MPI_Send()
    }
    double time_start = MPI_Wtime();
	MPI_Status status;
    if (rank==0){

    }
    else{

    }
	MPI_Finalize();
    return 0;
}
