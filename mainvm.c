#include "stdint.h"
#include "mainmem.h"
#include "cpu.h"
#include "stdio.h"
#include "bootstrap.h"

int main(){
    init();
    uint16_t* insts=inpASM();
    for(int i=0;i<1024;i++){
        writeRam(i,insts[i]);
    }
    uint16_t addr=0U;
    uint16_t max=50000U;
    while(parseInst(&addr,returnRAM())&&(max!=0U)){max-=1U;}
    return 0;
}