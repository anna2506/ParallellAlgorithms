#include <stdio.h>
#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char **argv)
{
	int rank;
	MPI_Init(&argc, &argv);
	MPI_File fh;
	char buf[10];
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        FILE* fh = fopen("file1.txt","wb+");
        if(fh==NULL){
            printf("failed to open file: permission issue ?\n");
            exit(1);
            }
        for (int i=0; i < 10; i++){
            fprintf(fh,"bulky text ");
        }
        fclose(fh);
    }
	MPI_File_open(MPI_COMM_WORLD, "file1.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, rank * 10, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
	MPI_File_read_all(fh, buf, 10, MPI_CHAR, MPI_STATUS_IGNORE);
	printf("process %d, buf=%s\n", rank, buf);
	MPI_File_close(&fh);
	MPI_Finalize();
}