#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <iostream>
#define n 1000
using namespace std;

void smod5(void *a, void *b, int *l, MPI_Datatype *type) {
	int i;
	for (i = 0; i < *l; i++)
		((int*)b)[i] = (((int*)a)[i] + ((int*)b)[i]) % 5;
}

void find_max(void *a, void *b, int *l, MPI_Datatype *type) {
	for (int i = 0; i < *l; i++)
		((int*)b)[i] = max(((int*)a)[i], ((int*)b)[i]);
}

int main(int argc, char **argv)
{
	int rank, size, i;
	int a[n];
	int b[n];
    int b_mpi_max[n];
	MPI_Init(&argc, &argv);
	MPI_Op op;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (i = 0; i < n; i++){
        a[i] = i + rank + 1;
    } 
	printf("process %d a[0] = %d\n", rank, a[0]);

	MPI_Op_create(&smod5, 1, &op);
	MPI_Reduce(a, b, n, MPI_INT, op , 0, MPI_COMM_WORLD);
	MPI_Op_free(&op);

	if (rank == 0){
        printf("b[0] = %d\n", b[0]);
    }

    // part for MPI_MAX
    MPI_Reduce(a, b_mpi_max, n, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    //my max function
    MPI_Op_create(&find_max, 1, &op);
	MPI_Reduce(a, b, n, MPI_INT, op , 0, MPI_COMM_WORLD);
	MPI_Op_free(&op);
    if (rank == 0){
        cout << "Maximum found by MPI_MAX b_mpi_max[0] = " << b_mpi_max[0] << endl;
        cout << "Maximum found in my functions b[0] = " << b[0] << endl;
    }
	MPI_Finalize();
}