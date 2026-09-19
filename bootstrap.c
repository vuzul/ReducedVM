#include "stdint.h"
#include "mainmem.h"
#include "bootstrap.h"
#include <stdio.h>
#include <string.h>

static char input[50];
static uint8_t intVals[256];
static uint16_t resL[1024];
static int resP=0;
static int i=0;
uint16_t* inpASM(){
    FILE* readFile = NULL;
    FILE* inputStream = stdin;
    readFile = fopen("asm.rasm","r");
    if(readFile != NULL){
        inputStream = readFile;
    }
    intVals['A']=4;
    intVals['B']=1;
    intVals['C']=2;
    intVals['D']=3;
    intVals['R']=5;
    intVals['S']=6;
    intVals['M']=7;
    intVals['0']=8;
    intVals['1']=9;
    intVals['X']=10;
    intVals['I']=11;
    int endcond=0;
    while(!endcond){
        memset(input,0,49);
        fgets(input,49,inputStream);
        char check[4]={input[0],input[1],input[2],'\0'};
        printf("&%d\n",strcmp(check,"END"));
        if(strcmp(check,"END")!=0){
            printf("^%c,%d\n",input[i],i);
            if(input[i]!='/'){
                i=0;
                uint16_t res=0;
                uint8_t target=0;
                if(input[i+1]==' '){
                    target=intVals[input[i]];
                    i+=2;
                }
                res|=target<<13;
                uint8_t opcode=0;
                int doMainInst=1;
                switch(input[i]){
                    case 'A': switch(input[i+1]){
                        case 'D': switch(input[i+2]){
                            case 'D': opcode=0; i+=3; break;
                        }break;
                        case 'N': switch(input[i+2]){
                            case 'D': opcode=8; i+=3; break;
                        }break;
                    }break;
                    case 'S': switch(input[i+1]){
                        case 'U': switch(input[i+2]){
                            case 'B': opcode=1; i+=3; break;
                        }break;
                        case 'J': switch(input[i+2]){
                            case 'T': opcode=0; i+=3; break;
                        }break;
                    }break;
                    case 'M': switch(input[i+1]){
                        case 'U': switch(input[i+2]){
                            case 'L': opcode=2; i+=3; break;
                        }break;
                    }break;
                    case 'C': switch(input[i+1]){
                        case 'L': switch(input[i+2]){
                            case 'T': opcode=4; i+=3; break;
                        }break;
                        case 'E': switch(input[i+2]){
                            case 'Q': opcode=5; i+=3; break;
                        }break;
                        case 'G': switch(input[i+2]){
                            case 'T': opcode=6; i+=3; break;
                        }break;
                        case 'N': switch(input[i+2]){
                            case 'Q': opcode=7; i+=3; break;
                        }break;
                    }break;
                    case 'I': switch(input[i+1]){
                        case 'N': switch(input[i+2]){
                            case 'P': opcode=3; i+=3; break;
                        }break;
                    }break;
                    case 'B': switch(input[i+1]){
                        case 'O': switch(input[i+2]){
                            case 'R': opcode=9; i+=3; break;
                        }break;
                        case 'S': switch(input[i+2]){
                            case 'L': opcode=14; i+=3; break;
                            case 'R': opcode=15; i+=3; break;
                        }break;
                    }break;
                    case 'X': switch(input[i+1]){
                        case 'O': switch(input[i+2]){
                            case 'R': opcode=10; i+=3; break;
                        }break;
                    }break;
                    case 'N': switch(input[i+1]){
                        case 'A': switch(input[i+2]){
                            case 'D': opcode=11; i+=3; break;
                        }break;
                        case 'O': switch(input[i+2]){
                            case 'R': opcode=12; i+=3; break;  
                        }break;
                        case 'X': switch(input[i+2]){
                            case 'R': opcode=13; i+=3; break;
                        }break;
                    }case 'P': switch(input[i+1]){
                        case 'S': switch(input[i+2]){
                            case 'H': {
                                resL[resP]=0b1000000010000110;
                                resP++;
                                resL[resP]=0b1010000000000000|intVals[input[i+4]];
                                resP++;
                                resL[resP]=0b1100000001101001;
                                resP++;
                                doMainInst=0;
                            }break;
                        }break;
                        case 'O': switch(input[i+2]){
                            case 'P': {
                                resL[resP]=0b1100001001101001;
                                resP++;
                                resL[resP]=0b1000000010000110;
                                resP++;
                                resL[resP]=0b10000101|(intVals[input[i+4]]<<13);
                                resP++;
                                doMainInst=0;
                            }break;
                        }break;
                    }break;
                    
                }
                if(doMainInst){
                    res|=opcode<<9;
                    i+=1;
                    int op0=intVals[input[i]];
                    i+=2;
                    int op1=intVals[input[i]];
                    i+=2;
                    printf("#%c",input[i]);
                    int jflag=input[i]=='J';
                    res|=jflag<<8;
                    res|=op0<<4;
                    res|=op1;
                    printf("$%b,%b,%b,%b,%b,%b\n",target,opcode,jflag,op0,op1,res);
                    resL[resP]=res;
                    resP++;
                    printf("##############%s\n",input);
                    if(op0==11|op1==11){
                        memset(input,0,49);
                        fgets(input,49,inputStream);
                        int16_t s;
                        sscanf(input,"%hd",&s);
                        i=0;
                        printf("#%d\n",s);
                        printf("$%b,%b,%b,%b\n",target,opcode,s,res);
                        resL[resP]=s;
                        resP++;
                    }
                }
            }
            i=0;
        }else{
            endcond=1;
        }
    }
    if(readFile){
        fclose(readFile);
    }
    return resL;
}
