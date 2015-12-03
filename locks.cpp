//
// Created by mereckaj on 12/2/15.
//

#include "Headers/locks.hpp"

void Bakery::init(int mt) {
    using namespace std;
    maxThreads = (unsigned int) mt;
    entering = new volatile bool[maxThreads];
    numbers = new volatile UINT[maxThreads];
    counter = 0;
}

void Bakery::acquire(int tid) {
    entering[tid] = true;
    numbers [tid] = 1 + max();
    entering[tid] = false;
    for(UINT i = 0; i < maxThreads;i++){
        while(entering[i]);
        while(numbers[i] != 0 && ( numbers[tid] > numbers[i]  || (numbers[tid] == numbers[i] && tid > i)));
    }
}

void Bakery::release(int tid) {
    numbers[tid] = 0;
}

void Bakery::inc(){
    counter++;
}
UINT Bakery::max() {
    UINT max;
    for(UINT i = 0; i < maxThreads;i++){
        if (numbers[i] > max){
            max = numbers[i];
        }
    }
}
