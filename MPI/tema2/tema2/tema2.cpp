#include <iostream>
#include "mpi.h"

using namespace std;

int main() {

    int rank, size, number, processRank;
    int vector[] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30 };
    int vectorSize = sizeof(vector) / sizeof(vector[0]);

    //initialize the MPI 
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

   

    //if we are on the rank 0, the element that have to be find is send to the rest of processes otherwise, every process !=0 will receive the element to search for
    if (rank == 0) {
        cout << "Element to find: ";
        cin >> number;

        for (processRank = 1; processRank < size; processRank++)
            MPI_Send(&number, 1, MPI_INT, processRank, 1, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(&number, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
   
    //i will calculate depending on the current process rank the interval to search in
    int start = (rank * vectorSize) / size;
    int end = ((rank + 1) * vectorSize) / size;
    int ok = 0;
    cout << start << " " << end << " " << endl;
    for (int index = start; index < end && ok == 0; index++) {
        if (vector[index] == number && index < vectorSize) {
            cout << "Element was found at the position " << index << "\n";
            ok = 1;
        }
    }
   

    MPI_Finalize();

}