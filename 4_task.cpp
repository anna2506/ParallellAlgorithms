#include <iostream>
#include "mpi.h"
using namespace std;
int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, n, i, message;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{
		cout << "Hello from process " << rank << "\n";
		for (i  = 1; i < n - 1; i++) {
            MPI_Send(&rank, i, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
            cout << "Sending message" << endl;
			MPI_Recv(&message, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			cout << "Hello from process " << message << endl;
		}
	}
	else MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}