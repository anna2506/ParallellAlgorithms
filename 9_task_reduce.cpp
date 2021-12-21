#include <iostream>
#include <mpi.h>
#include <cmath>

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
    // variable to calculate sum in process in exact moment in time
    int process_sum = 0;
    for (int i = 0; i < vector_size; i++){
        process_sum += vector[i];
    }
    double time_finish;
    double time_start = MPI_Wtime();
    int final_sum = 0;
	MPI_Status status;
    MPI_Reduce(&process_sum, &final_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0) {
        time_finish = MPI_Wtime();
        cout<< "Total sum with MPI_Reduce = "<< final_sum - process_sum<< endl;
        cout<< "Time required to execute with MPI_Reduce "<< time_finish - time_start << endl;
        } 
	MPI_Finalize();
    return 0;
}
