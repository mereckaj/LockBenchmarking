#include "Headers/BakeryLock.hpp"
#include "Headers/helper.h"
#include "Headers/TestAndSetLock.hpp"
#include "Headers/locks.hpp"
#include "Headers/TestAndTestAndSetLock.hpp"
#include "Headers/MCS.hpp"
#include <iostream>
#include <assert.h>
#include <lcms.h>

#define NOPS 10000
#define NSECONDS 1

/*
 * 0 = Atomic Increment
 * 1 = Bakery lock
 * 2 = TestAndSet lock
 * 3 = TestAndTestAndSet lock (Optimistic)
 * 4 = TestAndTestAndSet lock (Pessimistic)
 * 5 = MCS
 */

#define LOCK_TYPE 5


BakeryLock bakeryLock;
TestAndSetLock testAndSetLock;
TestAndTestAndSetLock testAndTestAndSetLock;
MCSLock mcsLock;
volatile UINT64 counter= 0;
UINT64 tstart;

WORKER worker(void *vthread) {
    using namespace std;
    int tid = (int) ((size_t) vthread);
    UINT64 realCounter = 0;

#if LOCK_TYPE == 5
    /*
     * Get the thread local storages key for thsi thread
    */

    TLSINDEX tlsIndex;
    TLSALLOC(tlsIndex);
    /*
     * Create a node for this thread
     */
    QNode * node = new QNode();
    /*
     * Make the node local to this thread
     */
    TLSSETVALUE(tlsIndex, node);
#endif

    tstart = getWallClockMS();
    while (1) {
        for (int i = 0; i < NOPS; i++) {
#if LOCK_TYPE == 0
            InterlockedIncrement64(&counter);
            realCounter++;
#elif LOCK_TYPE == 1
            bakeryLock.acquire(tid);
            bakeryLock.inc();
            realCounter++;
            bakeryLock.release(tid);
#elif LOCK_TYPE == 2
            testAndSetLock.acquire();
            testAndSetLock.inc();
            realCounter++;
            testAndSetLock.release();
#elif LOCK_TYPE == 3
            testAndTestAndSetLock.acquireOptimistic();
            testAndTestAndSetLock.inc();
            realCounter++;
            testAndTestAndSetLock.release();
#elif LOCK_TYPE == 4
            testAndTestAndSetLock.acquirePessimistic();
            testAndTestAndSetLock.inc();
            realCounter++;
            testAndTestAndSetLock.release();
#elif LOCK_TYPE == 5
            mcsLock.acquire(mcsLock.lock,tlsIndex);
            mcsLock.inc();
//            cout << tid << endl;
            realCounter++;
            mcsLock.release(mcsLock.lock,tlsIndex);
#endif
        }
        if ((getWallClockMS() - tstart) > NSECONDS * 1000) {
            break;
        }
    }
    counters[tid] = realCounter;
}