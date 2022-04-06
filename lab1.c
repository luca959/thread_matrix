#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define nullptr NULL
void store(int row, int col,float *x){
 for (int i = 0; i < row; ++i)
  {
    for (int j = 0; j < col; j++)
    {
        x[i+j]=rand()%10+1;
    }
  }
  return ;
}

void print(int row, int col,float *x){
 for (int i = 0; i < row; ++i)
  {
    for (int j = 0; j < col; j++)
    {
      printf("x %d, y %d = %f\n", i , j , x[i+j]);
    }
  }
  printf("%s","--------------------------------\n");
  return ; 
}

float *multiplyMatrix(float *m1, float row1, int col1, float *m2, int row2, int col2)
{
    if (col1 != row2)
        return nullptr;

    float* ret = (float*) malloc(row1*col2);
    int i,j,k;
    for(i = 0; i < row1; i++) {
        for(j = 0; j < col2; j++) {
            for(k = 0; k < row2; k++) {
                ret[i+j] += m1[i+k] * m2[k+j];
            }
        }
    }

    return ret;
}
int main() {
    clock_t start = clock();
    // dichiarazione puntatori a matrici
    float *a,*b,*c,*r,*cr;
    srand(time(NULL));
    //Assegnazione M,N,P
    int m,n,p;
    printf("%s", "Inserisci M:");
    scanf("%d",&m);
    printf("%s", "Inserisci N:");
    scanf("%d",&n);
    printf("%s", "Inserisci P:");
    scanf("%d",&p);
    //stampa valori M,N,P
    printf("M: %d",m);
    printf("N: %d",n);
    printf("M: %d\n",p);
    //Creazioni Matrici A,B,C
    a= (float*) malloc(m*n);
    b= (float*) malloc(n*p);
    c= (float*) malloc(p*m);
    //inserimento valori matrici
    store(m,n,a);
    store(n,p,b);
    store(p,m,c);
    //Stampa matrici
    print(m,n,a);
    print(n,p,b);
    print(p,m,c);
    //Prodotto tra matrici
    r=multiplyMatrix(a,m,n,b,n,p);
    cr=multiplyMatrix(c,p,m,r,m,p);
    printf("%s","R=(A*B)\n");
    print(m,p,r);
    printf("%s","Finale=(C*R)\n");
    print(p,p,cr);
    //liberazione memoria
    free(a);
    free(b);
    free(c);
    free(r);
    free(cr);
    clock_t end = clock();
    printf("Tempo di esecuzione =  %f secondi \n", ((double)(end - start)) / CLOCKS_PER_SEC);
    return 0;
}
