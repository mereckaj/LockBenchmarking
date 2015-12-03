//
// Created by mereckaj on 12/3/15.
//

#include "Headers/TestAndSetLock.hpp"

using namespace std;
void TestAndSetLock::acquire() {
    while(InterlockedCompareExchange(&lock,true,false));
}

void TestAndSetLock::release() {
    InterlockedCompareExchange(&lock,false,true);
}

void TestAndSetLock::init() {
    cnt = 0;
    lock = false;
}

void TestAndSetLock::inc() {
    cnt++;
}

unsigned long long int TestAndSetLock::getCounter() {
    return cnt;
}
