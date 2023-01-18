#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int arg, char *argv[])
{

    // Basic Configuration
    int arrSize = 20;        // Size
    int key = 10;            // Key
    char *file = "data.txt"; // File Name
    int processors, i;       // Process arrSize, Process ID
    int processorRank;       // Gets the current processor rank

    // MPI Program
    MPI_Init(&arg, &argv);                         // Initialize the MPI execution environment
    MPI_Status status;                             // Structure that represents the status of the received message.
    MPI_Comm_size(MPI_COMM_WORLD, &processors);    // Determines the arrSize of the group associated with a communicator
    MPI_Comm_rank(MPI_COMM_WORLD, &processorRank); // Determines the rank of the calling process in the communicator
    int *buffer;                                   // Array stored the output

    // File Reading
    FILE *fp;

    // Calculating arrSize by dividing arrSize by process size
    int localsize = arrSize / processors;

    if (processorRank == 0)
    {
        // At initial stage of the program, import the file content
        fp = fopen(file, "r");
        if (fp == NULL)
        {
            perror("File Couldnt be read!");
            exit(1);
        }

        // Intialize process array with the array arrSize
        buffer = (int *)calloc(arrSize, sizeof(int));

        // Getting input from the file, single character at a time
        for (i = 0; i < arrSize; i++)
        {
            if (getc(fp) != '\0')
                buffer[i] = fgetc(fp);
        }

        // This routine may block until the message is received by the destination process.
        for (int i = 1; i < processors; i++)
        {
            MPI_Send((buffer + (i * localsize)), localsize, MPI_INT, i, 0, MPI_COMM_WORLD); // Performs a blocking send
        }
    }
    else
    {
        buffer = (int *)calloc(localsize, sizeof(int));
        // Blocking receive for a message
        MPI_Recv(buffer, localsize, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }
    for (int i = 0; i < localsize; i++)
    {
        if (buffer[i] == key)
        {
            printf("Process# %d -> Local Position: %d \n", processorRank, i);
        }
    }
    MPI_Finalize();
}
