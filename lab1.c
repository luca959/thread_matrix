#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

struct matrix{
    float *ptr;
    int row;
    int col;
};

void store(struct matrix x){
 for (int i = 0; i < x.row; ++i)
  {
    for (int j = 0; j < x.col; j++)
    {
        x.ptr[i*x.col+j]=rand()%10+1;
    }
  }
  return ;
}
void init(struct matrix x){
     for (int i = 0; i < x.row; ++i)
  {
    for (int j = 0; j < x.col; j++)
    {
        x.ptr[i*x.col+j]=0;
    }
  }
  return ;
}
void print(struct matrix x){
 for (int i = 0; i < x.row; ++i)
  {
    for (int j = 0; j < x.col; j++)
    {
      printf("x %d, y %d = %f\n", i , j , x.ptr[i*x.col+j]);
    }
  }
  printf("%s","--------------------------------\n");
  return ; 
}
void multiplyMatrix(struct matrix m1,struct matrix m2,struct matrix m3,int start,int end){
    if (m1.col != m2.row){
        printf("%s","errore moltiplicazione matrici");
        exit(1);
    }
    for (int i = start; i < end; ++i) {
        for (int k = 0; k < m2.col; ++k) {
            float acc = 0;
            for (int j = 0; j < m1.col; ++j){
                acc += m1.ptr[i * m1.col + j] * m2.ptr[j * m2.col + k];
            }
            m3.ptr[i * m3.col + k] = acc;
        }
        printf("\n");
    }
  
}

int main() {
    clock_t s = clock();
    // dichiarazione puntatori a matrici
    struct matrix a,b,c,r,cr;
    srand(time(NULL));
    //Assegnazione M,N,P
    int m,n,p,nblock,end,start=0;
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
    a.ptr= (float*) malloc(m*n);
    b.ptr= (float*) malloc(n*p);
    c.ptr= (float*) malloc(p*m);
    a.row=m;
    a.col=n;
    b.row=n;
    b.col=p;
    c.row=p;
    c.col=m;
    //inserimento valori matrici
    store(a);
    store(b);
    store(c);
    //Stampa matrici
    print(a);
    print(b);
    print(c);
    printf("%s", "Inserisci numero di blocchi di R=A*B:");
    scanf("%d",&nblock);  
    if (nblock > a.row)
    {
        printf("%s","errore numero di blocchi > numero di righe");
        exit(1);
    }
    //creo matrice risultato   
    r.ptr=(float*) malloc(m*p);
    r.row=m;
    r.col=p;
    init(r);
    //prendo i vari blocchi INIZIO
    if(a.row!=nblock){
        end=a.row/nblock;
        for (int k = 0; k <nblock;k++)
        {
            multiplyMatrix(a,b,r,start,end);
            start=end;
            end+=end;
            printf("\n");
        }
    }
    else{

        for (int k = 1; k <=nblock;k++)
            {   end=k;
                multiplyMatrix(a,b,r,start,end);
                start=end;

            }       
    }
    print(r);
    cr.ptr=(float*) malloc(p*p);
    cr.row=p;
    cr.col=p;
    init(cr);
    printf("%s", "Inserisci numero di blocchi di C*R:");
    scanf("%d",&nblock);  
    start=0;
     if(a.row!=nblock){
        end=a.row/nblock;
        for (int k = 0; k <nblock;k++)
        {
            multiplyMatrix(c,r,cr,start,end);
            start=end;
            end+=end;
            printf("\n");
        }
    }
    else{

        for (int k = 1; k <=nblock;k++)
            {   end=k;
                multiplyMatrix(c,r,cr,start,end);
                start=end;
            }       
    }

     print(cr);

    //PRENDO I VARI BLOCCHI FINE
    //liberazione memoria
    free(a.ptr);
    free(b.ptr);
    free(c.ptr);
    free(r.ptr);
    free(cr.ptr);

    clock_t e = clock();
    printf("Tempo di esecuzione =  %f secondi \n", ((double)(e - s)) / CLOCKS_PER_SEC);
    return 0;
}
