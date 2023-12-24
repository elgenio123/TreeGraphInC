#include <omp.h>
#include <time.h>
#define SIZE 100000

// Function type definition for functions that take an int parameter and return void
typedef void (*FunctionPtr)(int[]);

void nonParallelizedLoop(int array[]);
void parallelizedLoop(int array[]);
void executeFunction(FunctionPtr func1, int a1[],FunctionPtr func2, int a2[]);