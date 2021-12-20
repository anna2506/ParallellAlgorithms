#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
	int rank, size;
    // initializing MPI library
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int max_length = 1000000;
    
    double time_start = MPI_Wtime();
    // check that we have exactly 2 processes in our program
    if (size != 2){
        cout << "Error! In this programm there should be only 2 processes";
        return 0;
    }
	MPI_Status status;
    double T, R, s;
    // start iterating in message length
    for (int length = 1; length <= max_length; length *= 10){
        char message[length];
        fill_n(message, length, 'a');
        int L = length * sizeof(char);
        // cout << message << endl;
        if (rank == 0){
            // if rank is 0, than we first send, then receive message
            double time_start;
            time_start = MPI_Wtime();
            for(int i = 0; i < 10; i ++){
                MPI_Send(&message, length, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
            }
            for (int i = 0; i < 10; i++){
                MPI_Recv(&message, length, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);
            }
        }
        else{
            // if rank is 1, we first receive, then send messages
            double time_finish;
            for(int i = 0; i < 10; i++){
                MPI_Recv(&message, length, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
            }
            for(int i = 0; i < 10; i++){
                MPI_Send(&message, length, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
            }
            time_finish = MPI_Wtime();
            // calculating all the values
            T = (time_finish - time_start) * 1000000;
	        R = 2 * L * 10 / T / 1024 / 1024;
            s = T / 2 / 10;
            cout << "Time taken to send and receive message (seconds) = "  << (time_finish - time_start)*1000;
            cout << " Message length = " << length;
            cout << " L = " << L;
            cout << " Brandwith (Mb/s) " << R;
            cout << " Latency = " << s << endl;
        }
    }
	MPI_Finalize();
    return 0;
}

