
#ifndef others_h
#define others_h
    #include <omp.h>
    #include <time.h>
    #include "tree.h"
    #define SIZE 100000

    // Function type definition for functions that take an int parameter and return void
    typedef unsigned long long (FunctionPtr)(unsigned long long);

    void nonParallelizedLoop(int array[]);
    void parallelizedLoop(int array[]);

    void executeFunction(FunctionPtr func1, unsigned long long a1,FunctionPtr func2, unsigned long long a2);
    unsigned long long fib(unsigned long long n);
    unsigned long long fib_dynamic(unsigned long long n);
#endif