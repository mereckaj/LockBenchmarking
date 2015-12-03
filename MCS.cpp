//
// Created by mereckaj on 12/3/15.
//

#include "Headers/MCS.hpp"
#include <iostream>
using namespace std;
#include "Headers/helper.h"

int lineSize = getCacheLineSz();

template <typename T>
void *Aligned<T>::operator new(size_t t) {
    size_t sz = (sz + lineSize - 1) / lineSize * lineSize;
    return _aligned_malloc(sz, lineSize);
}

void Aligned<T>::operator delete(void *pVoid) {
    _aligned_free(pVoid);
}

inline void MCSLock::acquire(pthread_key_t tlsIndex) {
    volatile QNode *qn = (QNode *) TLSGETVALUE(tlsIndex);
    qn->next = NULL;
    volatile QNode *prev = (QNode *) InterlockedExchangePointer((PVOID) & lock, (PVOID) qn);
    if (prev == NULL) {
        return;
    }
    qn->waiting = true;
    prev->next = qn;
    while (qn->waiting);
    cout << "Locked" << endl;
}

inline void MCSLock::release(pthread_key_t tlsIndex) {
    volatile QNode *qn = (QNode *) TLSGETVALUE(tlsIndex);
    volatile QNode *suc;
    if (!(suc = qn->next)) {
        if (InterlockedCompareExchangePointer((PVOID) & lock, NULL, (PVOID) qn) == qn) {
            return;
        }
        do {
            suc = qn->next;
        } while (!suc);
    }
    suc->waiting = false;
    cout << "Unlocked" << endl;
}

void MCSLock::init() {
    lock = new QNode();
}

void MCSLock::inc() {
    cnt++;
}

UINT64 MCSLock::getCounter() {
    return cnt;
}
