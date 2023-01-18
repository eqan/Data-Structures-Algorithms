#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    time_t t;
    int processor;
    int processRank;
    int arrSize = atoi(argv[1]);
    int startfrom[4] = {0, 34, 51, 76};
    int endto[4] = {33, 50, 75, 100};
    int frequency[4] = {0, 0, 0, 0};

    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &processor);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);

    int localSize = arrSize / processor;

    if (processRank == 0)
    {
        int *randomNumbersArray = (int *)calloc(arrSize, sizeof(int));
        srand((unsigned)time(&t));
        printf("\nElements: ");
        for (int i = 0; i < arrSize; i++)
        {
            randomNumbersArray[i] = rand() % 100;
            printf("%d ", randomNumbersArray[i]);
        }

        printf("\nProcessor #%d -> Values: ", processRank);
        for (int i = 0; i < localSize; i++)
        {
            printf(" %d ", randomNumbersArray[i]);
            if (randomNumbersArray[i] >= startfrom[0] && randomNumbersArray[i] <= endto[0])
            {
                frequency[0] += 1;
            }
            if (randomNumbersArray[i] >= startfrom[1] && randomNumbersArray[i] <= endto[1])
            {
                frequency[1] += 1;
            }
            if (randomNumbersArray[i] >= startfrom[2] && randomNumbersArray[i] <= endto[2])
            {
                frequency[2] += 1;
            }
            if (randomNumbersArray[i] >= startfrom[3] && randomNumbersArray[i] <= endto[3])
            {
                frequency[3] += 1;
            }
        }
        printf("\n\nBefore Reduction:");
        for (int i = 0; i < 4; i++)
        {
            printf("\nBin %d From -> %d - To -> %d - Frequency -> %d", i + 1, startfrom[i], endto[i], frequency[i]);
        }
        for (int i = 1; i < processor; i++)
        {
            MPI_Send((randomNumbersArray + (i * localSize)), localSize, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        int TotalFrequency[4] = {0, 0, 0, 0};
        for (int i = 0; i < 4; i++)
        {
            TotalFrequency[i] += frequency[i];
            frequency[i] = 0;
        }
        for (int i = 1; i < processor; i++)
        {
            MPI_Recv(frequency, 4, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            for (int i = 0; i < 4; i++)
            {
                TotalFrequency[i] += frequency[i];
                frequency[i] = 0;
            }
        }
        printf("\n\nAfter Reduction: ");
        for (int i = 0; i < 4; i++)
        {
            printf("\nBin %d From -> %d - To -> %d - Frequency -> %d", i + 1, startfrom[i], endto[i], TotalFrequency[i]);
        }
    }
    else
    {
        int *processArray = (int *)calloc(localSize, sizeof(int));
        MPI_Recv(processArray, arrSize, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("\n\nProcessor #%d -> Values: ", processRank);
        for (int i = 0; i < localSize; i++)
        {
            printf(" %d ", processArray[i]);
            if (processArray[i] >= startfrom[0] && processArray[i] <= endto[0])
            {
                frequency[0] += 1;
            }
            if (processArray[i] >= startfrom[1] && processArray[i] <= endto[1])
            {
                frequency[1] += 1;
            }
            if (processArray[i] >= startfrom[2] && processArray[i] <= endto[2])
            {
                frequency[2] += 1;
            }
            if (processArray[i] >= startfrom[3] && processArray[i] <= endto[3])
            {
                frequency[3] += 1;
            }
        }
        printf("\n\nBefore Reduction: ");
        for (int i = 0; i < 4; i++)
        {
            printf("\nBin %d From -> %d - To -> %d - Frequency -> %d", i + 1, startfrom[i], endto[i], frequency[i]);
        }
        MPI_Send(frequency, 4, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}
