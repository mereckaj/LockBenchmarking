//
// Created by mereckaj on 12/2/15.
//

#ifndef ARCHLAB2_LOCKS_HPP
#define ARCHLAB2_LOCKS_HPP

#include <iostream>
#include "helper.h"

class Bakery{
public:

    void acquire(int i);

    void release(int i);

    void init(int mt);

    volatile unsigned int counter;

private:

    volatile bool* entering;

    volatile UINT* numbers;

    inline unsigned int max();

    unsigned int maxThreads;

    void inc();
};
#endif //ARCHLAB2_LOCKS_HPP
