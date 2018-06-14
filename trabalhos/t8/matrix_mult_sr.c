
#include <mpi.h>
#include <stdio.h>

#define SIZE 4      /* Size of matrices */

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];


void fill_matrix(int m[SIZE][SIZE])
{
  static int n=0;
  int i, j;
  for (i=0; i<SIZE; i++)
    for (j=0; j<SIZE; j++)
      m[i][j] = n++;
}

void print_matrix(int m[SIZE][SIZE])
{
  int i, j = 0;
  for (i=0; i<SIZE; i++) {
    printf("\n\t| ");
    for (j=0; j<SIZE; j++)
      printf("%*d", 6, m[i][j]);
    printf("|");
  }
}


int main(int argc, char *argv[])
{
  int myrank, nproc, from, to, i, j, k;
  int tag_A = 0;
  int tag_B = 1;
  MPI_Status status;
  
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank); /* who am i */
  MPI_Comm_size(MPI_COMM_WORLD, &nproc); /* number of processors */

  if (SIZE%nproc!=0) {
    if (myrank==0) printf("Matrix size not divisible by number of processors\n");
    MPI_Finalize();
    return -1;
  }

  from = myrank * SIZE/nproc;
  to = (myrank+1) * SIZE/nproc;

  /* Process 0 fills the input matrices and broadcasts them to the rest */
  /* (actually, only the relevant stripe of A is sent to each process) */

  if (myrank==0) {
    fill_matrix(A);
    fill_matrix(B);
  }

   // Broadcast B to other process
   MPI_Bcast(B, SIZE*SIZE, MPI_INT, 0, MPI_COMM_WORLD);
   // Send "Total of lines" / "Number of process" lines to other process
   int line = SIZE * SIZE / nproc;
   int aux1[line], aux2[line];
   MPI_Scatter(A, line, MPI_INT, aux1, line, MPI_INT, 0, MPI_COMM_WORLD);
   //MPI_Barrier(MPI_COMM_WORLD);
   
   int sum = 0;
   for (i = 0; i < line; i++){
      for (j = 0; j < line; j++){
         sum = sum + aux1[j] * B[j][i];
      }
      aux2[i] = sum;
      sum = 0;
   }

   MPI_Gather (aux2, line, MPI_INT, C, line, MPI_INT, 0, MPI_COMM_WORLD);
   
   //MPI_Barrier(MPI_COMM_WORLD);

  if (myrank==0) {
    printf("\n\n");
    print_matrix(A);
    printf("\n\n\t       * \n");
    print_matrix(B);
    printf("\n\n\t       = \n");
    print_matrix(C);
    printf("\n\n");
  }

  MPI_Finalize();
  return 0;
}



