#ifndef MAINMEM_H
#define MAINMEM_H

#include "stdint.h"

uint16_t readRam(int addr);
void writeRam(int addr,uint16_t byte);

uint16_t* returnRAM(void);
uint16_t* returnMEM(void);

#endif