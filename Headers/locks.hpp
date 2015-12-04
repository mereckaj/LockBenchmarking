//
// Created by mereckaj on 12/2/15.
//

#include "BakeryLock.hpp"
#include "TestAndSetLock.hpp"
#include "TestAndTestAndSetLock.hpp"
#include "MCS.hpp"

#ifndef ARCHLAB2_LOCKS_HPP
#define ARCHLAB2_LOCKS_HPP

extern volatile UINT64 counter;
extern int maxThreads;
extern UINT64* counters;
extern BakeryLock bakeryLock;
extern TestAndSetLock testAndSetLock;
extern TestAndTestAndSetLock testAndTestAndSetLock;
extern MCSLock mcsLock;

WORKER worker(void* vthread);
#endif //ARCHLAB2_LOCKS_HPP
