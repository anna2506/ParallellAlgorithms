#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
	int rank, size, first_index, last_index, dot_product = 0;
	int vector_size = 1000000;
    int vector_1[vector_size], vector_2[vector_size];
    // initializing MPI library
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Status status;
	
	if (rank == 0) {
        // filling arrays
		fill_n(vector_1, vector_size, 1);
        fill_n(vector_2, vector_size, 1);
        // batch size which will be sent tp processes
        int batch = vector_size / size;
		first_index = 0;  // start iterating from the 0 index
		last_index = first_index + batch; // get the first batch from vector
		
		for (int i = 1; i < size; i++) {
			first_index = last_index;
            (first_index + batch) < vector_size ? last_index = first_index + batch : last_index = vector_size; // check if first index + batch size is less than vector size
			// sending parts of vectors to processes
			MPI_Send(&vector_1[first_index], last_index - first_index, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(&vector_2[first_index], last_index - first_index, MPI_INT, i, 1, MPI_COMM_WORLD);
		}
		int tmp_sum = 0;
		first_index = 0;
		last_index = first_index + batch;
        // get dot product of parts of two vectors
		for (int i = first_index; i < last_index; i++){
            dot_product += (vector_1[i] * vector_2[i]);
        }
		for (int i = 1; i < size; i++) {
            // get message with temporary sum of parts pf two vectors
			MPI_Recv(&tmp_sum, batch, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
			dot_product += tmp_sum;
		}
        // printing sum of dot products of two vectors
		printf("Dot product of two vectors is %d\n", dot_product);
	}
	
	else {
        int batch = vector_size / size;
        // getting messages from 0 process
		MPI_Recv(&vector_1, batch, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&vector_2, batch, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		
		for (int i = 0; i < batch; i++){
            dot_product += (vector_1[i] * vector_2[i]);
        }
        // sending message with dot product 
		MPI_Send(&dot_product, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();
	return 0;
}




