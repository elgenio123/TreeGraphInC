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
void executeFunction(FunctionPtr func1, int a1[],FunctionPtr func2, int a2[]) {
    int start, end;
    double first, second;
    start = clock();
    func1(a1);
    end = clock();
    first = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
    func2(a2);
    end = clock();
    second = ((double) (end - start)) / CLOCKS_PER_SEC; 

    printf("First:  %f\n", first);
    printf("Second:  %f \n", second);
}