#include <stdio.h>
#include "others.h"

#define SIZE 100000


void nonParallelizedLoop(int array[]) {
    for (int i = 0; i < SIZE; ++i) {
        array[i] = i * i;
    }
}

void parallelizedLoop(int array[]) {
    #pragma omp parallel for
    for (int i = 0; i < SIZE; ++i) {
        array[i] = i * i;

    }
}
//takes two functions and tells which function took more cpu time
 void executeFunction(FunctionPtr func1, unsigned long long a1,FunctionPtr func2, unsigned long long a2) {
    int start, end;
    double first, second;
    start = clock();
    unsigned long long val1=func1(a1);
    end = clock();
    first = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
    unsigned long long val2=func2(a2);
    end = clock();
    second = ((double) (end - start)) / CLOCKS_PER_SEC; 

    printf("Fib of %llu is %llu with time:  %f\n",a1,val1, first);
    printf("Fib_dynamic of %llu is %llu with time:  %f\n",a2,val2, second);
}

unsigned long long fib(unsigned long long n){
    if (n==0 || n==1)
        return 1;
    else
        return fib(n-1)+fib(n-2);
}
unsigned long long fib_dynamic(unsigned long long n){
    unsigned long long u0, u1, u;
    if(n==0)
        return 0;
    u0 = 0;
    u1 = 1;
    for(int i=0; i<n; i++){
        u = u0 + u1;
        u0 = u1;
        u1 = u;
    }
    return u;
}