#ifndef CPU_H
#define CPU_H

#include "stdint.h"

void init();
uint16_t parseInst(uint16_t* addr,uint16_t* RAM,uint16_t* MEM);

#endif