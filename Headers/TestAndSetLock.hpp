//
// Created by mereckaj on 12/3/15.
//

#ifndef ARCHLAB2_TESTANDSETLOCK_HPP
#define ARCHLAB2_TESTANDSETLOCK_HPP

#include "helper.h"

class TestAndSetLock{
public:
    void acquire();

    void release();

    void init();

    void inc();

    UINT64 getCounter();
private:
    volatile UINT64 cnt;
    volatile bool lock;

};
#endif //ARCHLAB2_TESTANDSETLOCK_HPP
