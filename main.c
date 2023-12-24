#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "graph.h"
#include "others.h"


int main() {

    int array1[SIZE];
    int array2[SIZE];

    executeFunction(parallelizedLoop, array1, nonParallelizedLoop, array2);
    printf("Hello baby");
    
    return 0;
}