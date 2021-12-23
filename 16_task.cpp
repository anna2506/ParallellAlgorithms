#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	int rank, size, rank1;
	MPI_Init(&argc, &argv);
	MPI_Comm comm_revs;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Comm_split(MPI_COMM_WORLD, 1, size - rank, &comm_revs);
	MPI_Comm_rank(comm_revs, &rank1);
    cout << "Rank = " << rank << " Color = " << 1 << " key = " << size - rank << " rank1 = " << rank1 << endl;
	MPI_Comm_free(&comm_revs);
    if (rank == 0){
        cout << "Color = 1" << endl;
    }

    //replace color with rank % 2
    MPI_Comm_split(MPI_COMM_WORLD, rank % 2, size - rank, &comm_revs);
	MPI_Comm_rank(comm_revs, &rank1);
    cout << "Rank = " << rank << " Color = " << rank % 2 << " key = " << size - rank << " rank1 = " << rank1 << endl;
	MPI_Comm_free(&comm_revs);
    if (rank == 0){
        cout << "Color is replaced by rank % 2" << endl;
    }

    //replace color with rank % 3
    MPI_Comm_split(MPI_COMM_WORLD, rank % 3, size - rank, &comm_revs);
	MPI_Comm_rank(comm_revs, &rank1);
    cout << "Rank = " << rank << " Color = " << rank % 3 << " key = " << size - rank << " rank1 = " << rank1 << endl;
	MPI_Comm_free(&comm_revs);
    if (rank == 0){
        cout << "Color is replaced by rank % 3" << endl;
    }

	MPI_Finalize();
}