//
// Created by mereckaj on 12/3/15.
//

#include "Headers/MCS.hpp"
#include "Headers/helper.h"
#include <iostream>
#include <lcms.h>

using namespace std;
int lineSize = getCacheLineSz();

template <typename T>
void *Aligned<T>::operator new(size_t sz) {
    size_t alignment = (sz + lineSize - 1) / lineSize * lineSize;
    return  _aligned_malloc(sz, alignment);
}

template <typename T>
void Aligned<T>::operator delete(void *pVoid) {
    _aligned_free(pVoid);
}

void MCSLock::acquire(QNode** lock,TLSINDEX tlsIndex) {
    volatile QNode *qn = (QNode*) TLSGETVALUE(tlsIndex);
    qn->next = NULL;
    volatile QNode *pred = (QNode*) InterlockedExchangePointer((PVOID*) lock, (PVOID) qn);
    if (pred == NULL)
        return;
    qn->waiting = true;
    pred->next = qn;
    while (qn->waiting);
    cout << "Locked" << endl;
}

void MCSLock::release(QNode** lock,TLSINDEX tlsIndex) {
    volatile QNode *qn = (QNode*) TLSGETVALUE(tlsIndex);
    volatile QNode *succ;
    if (!(succ = qn->next)) {
        if (InterlockedCompareExchangePointer((PVOID*)lock, NULL, (PVOID) qn) == qn)
            return;
        do {
            succ = qn->next;
        } while(!succ);
    }
    succ->waiting = false;
    cout << "Unlocked" << endl;
}

void MCSLock::init() {
    lock = new QNode();
    cnt = 0;
}

void MCSLock::inc() {
    cnt++;
}

UINT64 MCSLock::getCounter() {
    return cnt;
}
