#include "mpi.h"
int main(int argc, char **argv)
{
	int rank;
	MPI_Comm intercomm;
    //int world_size;
    //MPI_Comm_size( MPI_COMM_WORLD, &world_size );
	MPI_Init(&argc, &argv);
	MPI_Comm_get_parent(&intercomm);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Send(&rank, 1, MPI_INT, 0, rank, intercomm);
    //MPI_Send(&world_size, 1, MPI_INT, 0, rank, intercomm);
	MPI_Finalize();
	return 0;
}