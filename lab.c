#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define M 8
#define N 8
#define P 8
#define BLOCK 4
float A[M][N];
float B[N][P];
float C[P][M];
float R[M][P];
float CR[P][P];
pthread_barrier_t barrier;

void store(int row,int col,float x[][col]){
 for (int i = 0; i < row; ++i)
  {
    for (int j = 0; j < col; j++)
    {
        x[i][j]=rand()%10+1;
    }
  }
  return ;
}
void print(int row,int col,float x[][col]){
 for (int i = 0; i < row; ++i)
  {
    for (int j = 0; j < col; j++)
    {
      printf("%f ", x[i][j]);
    }
    printf("\n");

  }
  printf("%s","--------------------------------\n");
}

void *mul(void *pt) {
  int myid;
  int it=M/BLOCK;
  myid = *((int *)pt);
  int x=it+(myid*2);
  printf("Thread %d\n", myid);
    for (int i=myid*2; i <x; ++i) {
        printf("i: %d \n",i);
        printf("it+i: %d  \n",x);

        for  (int k = 0; k < P; ++k) {
            for (int j = 0; j < N; ++j){
                R[i][k] +=A[i][j] *B[j][k];
            }
        }
    }

  // barriera
    pthread_barrier_wait(&barrier);
    
    for ( int l=myid*2; l< x; ++l) {
        for (int m = 0; m < P; ++m) {
            for (int n = 0; n < M; ++n){
                CR[l][m] +=C[l][n] *R[n][m];
            }
        }
    }
  return(0);
}
int main() {
  clock_t s = clock();
  pthread_barrierattr_t barrier_attr;
  pthread_barrier_init(&barrier, &barrier_attr, BLOCK);
  pthread_t tid[BLOCK];
  void *ret;
  int *ptr;
  store(M,N,A);
  store(N,P,B);
  store(P,M,C);
  print(M,N,A);
  print(N,P,B);
  print(P,M,C);

  for (int i = 0; i < BLOCK; i++) {
    ptr = malloc(sizeof(int));
    *ptr=i;
    pthread_create(tid+i, 0, mul, ptr);
  }
  for (int i = 0; i < BLOCK; i++) {
     pthread_join(tid[i],&ret);
  }
  print(M,P,R);
  print(P,P,CR);

  clock_t e = clock();
  printf("Tempo di esecuzione =  %f secondi \n", ((double)(e - s)) / CLOCKS_PER_SEC);
  return 0;
}