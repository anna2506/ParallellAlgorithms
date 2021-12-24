#include <stdio.h>
#include <iostream>
#include <fstream>
#include "mpi.h"
#define BUFSIZE 100

using namespace std;

void make_file(){
    ofstream outputFile;
    outputFile.open("file.txt");
    outputFile << "Here is a random text generated";
}

int main(int argc, char **argv)
{
	int bufsize, num, sum;
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_File fh;
    MPI_Info info;
	char buf[BUFSIZE];
    make_file(); // generate file.txt 
	MPI_File_open(MPI_COMM_WORLD, "file.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
	sum = 0;
	do {
		MPI_File_read(fh, buf, BUFSIZE, MPI_CHAR, &status);
		MPI_Get_count(&status, MPI_CHAR, &num);
		printf("buf=%s\n", buf);
		sum += num;
	} while (num >= BUFSIZE);
	MPI_File_close(&fh);
    cout << "Number of read symbols " << sum << endl;
    MPI_File_delete("file.txt", info); 
	MPI_Finalize();
}