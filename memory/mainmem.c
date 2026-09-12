#include "mainmem.h"

#include "stdint.h"

uint16_t RAM[65536];
uint16_t MEM[1024*1024];

uint16_t readRam(int addr){
    return RAM[addr];
}
void writeRam(int addr,uint16_t byte){
    RAM[addr]=byte;
}

uint16_t* returnRAM(){return RAM;}
uint16_t* returnMEM(){return MEM;}
