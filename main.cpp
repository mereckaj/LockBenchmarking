#include <stdlib.h>
#include <iostream>
#include "Headers/helper.h"
#include "Headers/locks.hpp"

int maxThreads;
UINT64* counters;
int main(int argc, char ** argv){
    using namespace std;

    ncpu = (unsigned int) getNumberOfCPUs();   // number of logical CPUs
    maxThreads = 2 * ncpu;       // max number of threads

    cout << "thread count/counter value" << endl;

    for(size_t i = 1; i <= maxThreads;i*=2 ){
        UINT64 incCounter = 0;
        THREADH workers[i];
        counters = new UINT64[i];
        UINT64** lel = &counters;
        /*
         * Init all the locks
         */

        memset(counters,i,0);
        bakeryLock.init(i);
        testAndSetLock.init();
        testAndTestAndSetLock.init();
        mcsLock.init();

        /*
         * Create all of the threads
         */
        for( size_t j = 0; j < i;j++){
            createThread(&workers[j],worker,(void*)j);
        }
        /*
         * Wait for threads to finish their work
         */
        waitForThreadsToFinish(i,workers);

        /*
         * Check to make sure the results are correct
         */
        for(size_t j = 0; j < i;j++){
            incCounter += counters[j];
        }

        /*
         * Print out the results
         */
//        cout << i << "/" << counter << "/" << incCounter <<"/"<<((double)counter/(double)incCounter) << endl;
        cout << i << "/" << bakeryLock.getCounter() << "/" << incCounter <<"/"<<((double)bakeryLock.getCounter()/(double)incCounter) << endl;
//        cout << i << "/" << testAndSetLock.getCounter() << "/" << incCounter <<"/"<<((double)testAndSetLock.getCounter()/(double)incCounter) << endl;
//        cout << i << "/" << testAndTestAndSetLock.getCounter() << "/" << incCounter <<"/"<<((double)testAndTestAndSetLock.getCounter()/(double)incCounter) << endl;
//        cout << i << "/" << testAndTestAndSetLock.getCounter() << "/" << incCounter <<"/"<<((double)testAndTestAndSetLock.getCounter()/(double)incCounter) << endl;
    }

    return EXIT_SUCCESS;
}