//
// Created by mereckaj on 12/3/15.
//

#ifndef ARCHLAB2_BAKERYLOCK_HPP
#define ARCHLAB2_BAKERYLOCK_HPP

#include <iostream>
#include "helper.h"

class BakeryLock {
public:
    void acquire(int i);

    void release(int i);

    void init(int mt);

    void inc();

    UINT64 getCounter();
private:

    volatile UINT64 cnt;

    volatile bool *entering;

    volatile UINT *numbers;

    inline unsigned int max();

    unsigned int maxThreads;

};

#endif //ARCHLAB2_BAKERYLOCK_HPP
