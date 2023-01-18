#include <mpi.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int processors, processRank; // variable for number of processes and process rank
  char *pattern = "GC";
  FILE *fp;
  FILE *file = "seq.txt";
  int size = 20;
  char *buffer; // Array stored the output

  // Initializing
  MPI_Init(&argc, &argv);
  MPI_Status status;
  MPI_Comm_size(MPI_COMM_WORLD, &processors);
  MPI_Comm_rank(MPI_COMM_WORLD, &processRank);

  fp = fopen(file, "r");
  if (fp == NULL)
  {
    perror("File Couldnt be read!");
    exit(1);
  }
  long length;
  FILE *f = fopen(file, "rb");

  if (f)
  {
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length);
    if (buffer)
    {
      fread(buffer, 1, length, f);
    }
    fclose(f);
  }

  if (buffer)
  {
    printf("Input Buffer: %s\n", buffer);
    if (processRank == 0)
    {
      int *count = (int *)calloc(processors, sizeof(int));
      for (int i = 0; i < processors; i++)
      {
        count[i] = 0;
      }
      int startFrom = processRank * (strlen(buffer) / processors);
      int endTo = startFrom + (strlen(buffer) / processors);
      for (int i = startFrom; i < endTo; i++)
      {
        if (buffer[i] == pattern[0])
        {
          if (i + 1 < endTo)
          {
            if (buffer[i + 1] == pattern[1])
            {
              printf("Pattern found at %d, %d\n", i, i + 1);
              count[0] += 1;
            }
          }
        }
      }
      for(int i=1; i < processors; i++)
      {
        MPI_Recv(&count[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
      }
      int TotalCount = 0;
      for (int i = 0; i < processors; i++)
      {
          TotalCount += count[i];
      }
      printf("Overall Findings: %d\n", TotalCount);
    }
    else
    {
      int count = 0;
      int startFrom = processRank * (strlen(buffer)/processors);
      int endTo = startFrom + (strlen(buffer)/processors);
      for(int i = startFrom; i< endTo; i++)
      {
        if(buffer[i] == pattern[0])
        {
          if(i+1 < endTo)
          {
            if(buffer[i+1] == pattern[1])
            {
              printf("Founded pattern at indexes: %d, %d\n", i, i+1);
              count+=1;
            }
          }
        }
      }
      printf("Overall Findings: %d\n", count);
      MPI_Send(&count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
  }
  MPI_Finalize();
}
