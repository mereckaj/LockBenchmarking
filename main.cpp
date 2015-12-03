#include <stdlib.h>
#include <iostream>
#include "Headers/helper.h"

int maxThreads;

int main(int argc, char ** argv){
    using namespace std;

    ncpu = getNumberOfCPUs();   // number of logical CPUs
    maxThreads = 2 * ncpu;       // max number of threads

    return EXIT_SUCCESS;
}