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
	MPI_Status status;
    // not the main process
    if (rank != 0){
        for(int i = 1; i <= (size - 1) / 2; i++){
            // this means that this process will receive temporary sums
            if (rank % 2 == 0){
                int tmp_sum;
                // receives message with temporary sum from any source with any tag
                MPI_Recv(&tmp_sum, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                process_sum += tmp_sum;
            }
            // this means process will send temporary sum
            else{
                MPI_Send(&process_sum, 1, MPI_INT, rank + (pow(2, i - 1)), 0, MPI_COMM_WORLD);
                break;
                }
        }
    }
    // if this process is the last one, we send the sum to the root process with id = 0
    if(rank == size - 1){
        MPI_Send(&process_sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        }
    // if the main process, calculate the whole sum
    if (rank == 0){
        // Calculate total sum
        int final_sum  = 0;
        MPI_Recv(&final_sum, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
        time_finish  = MPI_Wtime();
        cout << "Sum, calculated in point-to-point realisation = "<< final_sum << endl;
        cout << "Time required on point-to-point realisation "<< (time_finish - time_start) << endl;
    }
	MPI_Finalize();
    return 0;
}
