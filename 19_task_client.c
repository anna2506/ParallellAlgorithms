#include <stdio.h>
#include <string.h>
#include "mpi.h"
int main(int argc, char **argv)
{
	int rank;
    int message;
	MPI_Init(&argc, &argv);
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Comm intercomm;
    MPI_Status status;

	strcpy(port_name, argv[1]);
    printf("Attempt to connect\n");
	MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
    printf("Connected\n");
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    scanf("%d", &message);
	MPI_Send(&rank, 1, MPI_INT, 0, 0, intercomm);
    printf("Client sent value %d\n ", message);
    MPI_Recv(&rank, 1, MPI_INT, 0, 6, intercomm, &status);
    printf("Client got value %d\n ", rank);
	MPI_Finalize();
	return 0;
}