#include <iostream>
#include "helper.h"
#include "stdafx.h"
#include "helper.cpp"
#include "sharing.cpp"
#define SHARE_RANGE_UBOUND 100

using namespace std;

volatile int counter = 0;
void * fucked(void * i){
    cout<< "fucked" << endl;
}
int main() {
    int numberOfCpu = getNumberOfCPUs();

    for(UINT sharing = 0; sharing < SHARE_RANGE_UBOUND; sharing++){

        for(UINT threadNumber = 1; threadNumber < numberOfCpu; threadNumber++){

            UINT64 threadStart = getWallClockMS();
            THREADH threadArray[threadNumber];

            for(UINT thread = 0; thread < threadNumber;thread++){
                createThread(&threadArray[thread],worker,(void*)thread);
            }

            waitForThreadsToFinish(threadNumber,threadArray);
            UINT64 runtime = getWallClockMS() - threadStart;

            for(UINT thread = 0; thread < threadNumber;thread++){
                closeThread(threadArray[thread]);
            }
        }
    }
}