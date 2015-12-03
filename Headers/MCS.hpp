//
// Created by mereckaj on 12/3/15.
//

#ifndef ARCHLAB2_MCS_HPP
#define ARCHLAB2_MCS_HPP

#include <stddef.h>
#include "helper.h"

template <class T>
class Aligned{
public:
    void*operator new(size_t);
    void operator delete(void*);
};

class QNode : public Aligned<QNode>{
public:
    volatile bool waiting;
    volatile QNode* next;
};

class MCSLock{
public:
    inline void acquire(pthread_key_t tlsIndex);

    inline void release(pthread_key_t tlsIndex);

    void init();

    void inc();

    UINT64 getCounter();
private:
    volatile UINT64 cnt;
    volatile QNode* lock;
};


#endif //ARCHLAB2_MCS_HPP
