#include <stdlib.h>
#include <iostream>
#include "Headers/helper.h"
#include "Headers/locks.hpp"

int maxThreads;
int main(int argc, char ** argv){
    using namespace std;

    ncpu = (unsigned int) getNumberOfCPUs();   // number of logical CPUs
    maxThreads = 2 * ncpu;       // max number of threads

    cout << "thread count/counter value" << endl;

    for(size_t i = 1; i <= maxThreads;i*=2 ){
        THREADH workers[i];
        bakeryLock.init(i);
        testAndSetLock.init();
        for( size_t j = 0; j < i;j++){
            createThread(&workers[j],worker,(void*)j);
        }
        waitForThreadsToFinish(i,workers);
        cout << i << "/" << counter << endl;
        cout << i << "/" << bakeryLock.getCounter() << endl;
        cout << i << "/" << testAndSetLock.getCounter() << endl;
        cout << i << "/" << testAndTestAndSetLock.getCounter() << endl;
    }

    return EXIT_SUCCESS;
}