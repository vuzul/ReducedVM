#include <stdint.h>
#include <stdio.h>
#include "cpu.h"

static uint16_t J;
static uint16_t void16_t;
static uint16_t* JBranch[2]={&void16_t,&J};
static int16_t regs[256];
static enum regNames{
    regA=4,
    regB=1,
    regC=2,
    regD=3,
    regR=5,
    regS=6,
    regM=7,
    regN=8,
    regL=9,
    regX=10,
};
void init(){
    regs[regN]=0;
    regs[regL]=1;
    regs[regX]=(int16_t)-1;
}
static uint8_t ops[16]={0,regB,regC,regD,regA,regR,regS,regM,regN,regL,regX,0,0,0,0,0};

static void calc(int16_t* res,int16_t op0,int16_t op1,uint16_t* J){
    //ADD,SUB,MUL,INP,CLT,CEQ,CGT,CNQ||AND,BOR,XOR,NAD,NOR,NXR,BSL,BSR||SJT(TAR=4, J=0)
    //Arithmetic unit
    res[0]=op0+op1;//ADD
    res[1]=op0-op1;//SUB
    res[2]=op0*op1;//MUL
    res[3]=0;      //INP (input from lower 8 bits of instruction), see line 68 of this file
    //Compariasons
    res[4]=op0<op1;//Less than
    res[5]=op0==op1;//Equal
    res[6]=op0>op1;//Greater than
    res[7]=(op0==op1)^1;   //Not equal
    //Logic unit
    res[8]=op0&op1;   //AND
    res[9]=op0|op1;   //OR
    res[10]=op0^op1;  //XOR
    res[11]=(op0&op1)^(int16_t)-1;//NAND
    res[12]=(op0|op1)^(int16_t)-1;//NOR
    res[13]=(op0^op1)^(int16_t)-1;//XNOR
    //Barrel shifts
    res[14]=op0<<op1;//BSL, Barrel shift left
    res[15]=op0>>op1;//BSR, Barrel shift right
}


uint16_t parseInst(uint16_t* addr,uint16_t* RAM,uint16_t* MEM){
    int16_t res[16];//Initialising result array for ALU
    //Instructions are 16 bits long (see line 59 of this file for instruction format)
    uint16_t inst=RAM[*addr];//Instruction fetch
    regs[0]=0;//Voiding trash
    uint16_t oldA=regs[regA];
    regs[regR]=RAM[oldA];//Loading data from RAM
    //target,target,target,inst,inst,inst,inst,J,op0,op0,op0,op0,op1,op1,op1,op1
    int16_t op1=regs[inst&15];//Getting the second operand from the register file
    int16_t op0=regs[(inst>>4)&15];//Getting the first operand from the register file
    //ADD,SUB,MUL,INP,CLT,CEQ,CGT,CNQ||AND,BOR,XOR,NAD,NOR,NXR,BSL,BSR||SJT(TAR=0, J=0)
    uint8_t opcode=(inst>>9)&15;//Getting the opcode from the instruction
    uint8_t target=(inst>>13)&15;//Getting the target register from the instruction
    uint8_t writeInst=opcode==3;//Getting opcode to check for INP instruction
    printf("#%b",inst>>8);
    *JBranch[(((inst>>8)&1)^1)*(target==0)]=op0-1;//Setting the jump address
    calc(res,op0,op1,&J);//Sending data to ALU
    *addr+=writeInst;
    res[3]=RAM[*addr];//Overwriting the INP instruction result with the lower 8 bits of the instruction
    regs[target]=res[opcode];//Writing the result to the target register
    //printf("&%d,%d,%d\n",oldA,regs[regA],regs[regR]);
    RAM[oldA]=regs[regR];//Sending second half of data to RAM
    uint16_t addrBranch[2];//Initialising branch array for jump instructions
    addrBranch[0]=(*addr)+1;//Setting the next instruction address
    addrBranch[1]=J;//Setting the jump address
    *addr=addrBranch[((inst>>8)&1)*((regs[target]==0)^1)*(writeInst^1)];//Updating the program counter
    printf("$%b$\n",inst);//Debugging output for the value of the instruction
    printf("(%d)\n",*addr);
    printf("%hb,%d,%d,%d,%d,%c\n",regs[regR],regs[regA],regs[regB],regs[regC],regs[regD],regs[regD]);//Debugging output for the value of register D
    //printf("&%d,%b",*addr,RAM[*addr]);
    //printf("%d,%d,%d\n",RAM[0],RAM[127],RAM[128]);
    return RAM[*addr];
}