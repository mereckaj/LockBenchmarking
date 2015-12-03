//
// Created by mereckaj on 12/3/15.
//

#include "Headers/TestAndTestAndSetLock.hpp"
#include <iostream>
using namespace std;
void TestAndTestAndSetLock::acquirePessimistic() {
    do{
        while(lock){
            _mm_pause();
        }
    }while(InterlockedCompareExchange(&lock,true,false));
}
void TestAndTestAndSetLock::acquireOptimistic() {
    while(InterlockedCompareExchange(&lock,true,false)){
        while(lock){
            _mm_pause();
        }
    }
}

void TestAndTestAndSetLock::release() {
    lock = false;
}

void TestAndTestAndSetLock::init() {
    cnt = 0;
}

void TestAndTestAndSetLock::inc() {
    cnt++;
}

UINT64 TestAndTestAndSetLock::getCounter() {
    return cnt;
}
