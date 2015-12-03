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
int c = 0;
void BakeryLock::acquire(int tid) {
    //TODO: Memory fences
    entering[tid] = true;
    _mm_mfence();
    numbers [tid] = 1 + max();
    entering[tid] = false;
    for(UINT i = 0; i < maxThreads;i++){
        while(entering[i]);
        while(numbers[i] != 0 && ( numbers[tid] > numbers[i]  || (numbers[tid] == numbers[i] && tid > i)));
    }
    /*
     * Check that no more than 1 thread has the lock at one time.
     */
    c++;
    assert(c==1);
    c--;
}

void BakeryLock::release(int tid) {
    _mm_mfence();
    numbers[tid] = 0;
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
