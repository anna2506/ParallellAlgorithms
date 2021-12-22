#include <cstdlib>
#include <iostream>
#include "mpi.h"

double** generate_random_matrix(int rows, int columns){
    
    double** matrix = new double*[rows];
        for (int i = 0; i < rows; i++){
            matrix[i] = new double[columns];
        }
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                matrix[i][j] = (double)rand() / RAND_MAX;
            }
        }
    return matrix;
}

// function to make the values of matrix zero
double** null_matrix(int N){
    double** matrix = new double*[N];
        for (int i = 0; i < N; i++){
            matrix[i] = new double[N];
        }
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                matrix[i][j] = 0;
            }
        }
    return matrix;
}

int main(int argc, char **argv)
{
	int rank, size;
	double time_start, time_finish;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int size_matrix = 500;
	double **matrix_a, **matrix_b, **matrix_c; // initialize varibles for matrices
	// generate matrix A
	matrix_a = generate_random_matrix(size_matrix, size_matrix);
	// generate matrix B
	matrix_b = generate_random_matrix(size_matrix, size_matrix);
	// generate matrix C with zero values
	matrix_c = null_matrix(size_matrix);

	//matrix initialization by each process
	MPI_Barrier(MPI_COMM_WORLD); //barrier process synchronization
	// start timing for each process
	time_start  = MPI_Wtime();
	// matrix multiplication
	for (int i = 0; i < size_matrix; i++){
		for (int j = 0; j < size_matrix; j++){
			for (int k = 0; k < size_matrix; k++){
				matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
			}
		}
	}
	// end of timing
	time_finish = MPI_Wtime();
	// output the execution time of matrix multiplication at each process
	printf("Process %d takes %f seconds for multiplication of 2 matrices\n", rank, (time_finish - time_start));
	MPI_Finalize();
}