//
// Created by mereckaj on 12/2/15.
//

#include <assert.h>
#include "Headers/BakeryLock.hpp"

void BakeryLock::init(int mt) {
    using namespace std;
    maxThreads = (unsigned int) mt;
    entering = new volatile bool[maxThreads];
    numbers = new volatile UINT[maxThreads];
    cnt = 0;
}
void BakeryLock::acquire(int tid) {
    _mm_mfence();
    entering[tid] = true;
    numbers [tid] = 1 + max();
    entering[tid] = false;
    for(UINT i = 0; i < maxThreads;i++){
        while(entering[i]);
        _mm_mfence();
        while(numbers[i] != 0 && ( numbers[tid] > numbers[i]  || (numbers[tid] == numbers[i] && tid > i)));
    }
}

void BakeryLock::release(int tid) {
    numbers[tid] = 0;
    _mm_mfence();
}

void BakeryLock::inc(){
    cnt++;
}
UINT BakeryLock::max() {
    UINT max;
    for(UINT i = 0; i < maxThreads;i++){
        if (numbers[i] > max){
            max = numbers[i];
        }
    }
}


UINT64 BakeryLock::getCounter() {
    return cnt;
}
