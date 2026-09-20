#include "stdint.h"
#include "mainmem.h"
#include "bootstrap.h"
#include <stdio.h>
#include <string.h>

uint16_t* inpASM(void){
    static char input[50];
    static uint8_t intVals[256];
    static uint16_t resL[1024];
    static uint8_t resP=0;
    static uint8_t i=0;
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
        const char check[4]={input[0],input[1],input[2],'\0'};
        printf("&%d\n",strcmp(check,"END"));
        if(strcmp(check,"END")!=0){
            printf("^%c,%d\n",input[i],i);
            if(input[i]!='/'){
                i=0;
                uint16_t res=0;
                uint8_t target=0;
                if(input[i+1U]==' '){
                    target=intVals[input[i]];
                    i+=2U;
                }
                res|=(uint16_t)target<<13U;
                uint8_t opcode=0;
                uint8_t doMainInst=1;
                switch(input[i]){
                    case 'A': switch(input[i+1U]){
                        case 'D': switch(input[i+2U]){
                            case 'D': opcode=0; i+=3U; break;
                            default: break;
                        }break;
                        case 'N': switch(input[i+2U]){
                            case 'D': opcode=8; i+=3U; break;
                            default: break;
                        }break; default: break;
                        
                    }break;
                    case 'S': switch(input[i+1U]){
                        case 'U': switch(input[i+2U]){
                            case 'B': opcode=1; i+=3U; break;
                            default: break;
                        }break;
                        case 'J': switch(input[i+2U]){
                            case 'T': opcode=0; i+=3U; break;
                            default: break;
                        }break; default: break;
                    }break;
                    case 'M': switch(input[i+1U]){
                        case 'U': switch(input[i+2U]){
                            case 'L': opcode=2; i+=3U; break;
                            default: break;
                        }break; default: break;
                    }break;
                    case 'C': switch(input[i+1U]){
                        case 'L': switch(input[i+2U]){
                            case 'T': opcode=4; i+=3U; break;
                            default: break;
                        }break;
                        case 'E': switch(input[i+2U]){
                            case 'Q': opcode=5; i+=3U; break;
                            default: break;
                        }break;
                        case 'G': switch(input[i+2U]){
                            case 'T': opcode=6; i+=3U; break;
                            default: break;
                        }break;
                        case 'N': switch(input[i+2U]){
                            case 'Q': opcode=7; i+=3U; break;
                            default: break;
                        }break; default: break;
                    }break;
                    case 'I': switch(input[i+1U]){
                        case 'N': switch(input[i+2U]){
                            case 'P': opcode=3; i+=3U; break;
                            default: break;
                        }break; default: break;
                    }break;
                    case 'B': switch(input[i+1U]){
                        case 'O': switch(input[i+2U]){
                            case 'R': opcode=9; i+=3U; break;
                            default: break;
                        }break;
                        case 'S': switch(input[i+2U]){
                            case 'L': opcode=14; i+=3U; break;
                            case 'R': opcode=15; i+=3U; break;
                            default: break;
                        }break; default: break;
                    }break;
                    case 'X': switch(input[i+1U]){
                        case 'O': switch(input[i+2U]){
                            case 'R': opcode=10; i+=3U; break;
                            default: break;
                        }break; default: break;
                    }break;
                    case 'N': switch(input[i+1U]){
                        case 'A': switch(input[i+2U]){
                            case 'D': opcode=11; i+=3U; break;
                            default: break;
                        }break;
                        case 'O': switch(input[i+2U]){
                            case 'R': opcode=12; i+=3U; break;  
                            default: break;
                        }break;
                        case 'X': switch(input[i+2U]){
                            case 'R': opcode=13; i+=3U; break;
                            default: break;
                        }break; default: break;
                    }break;
                    case 'P': switch(input[i+1U]){
                        case 'S': switch(input[i+2U]){
                            case 'H': {
                                resL[resP]=0b1000000010000110;
                                resP++;
                                resL[resP]=0b1010000000000000U|intVals[input[i+4U]];
                                resP++;
                                resL[resP]=0b1100000001101001;
                                resP++;
                                doMainInst=0;
                            }break; default: break;
                        }break;
                        case 'O': switch(input[i+2U]){
                            case 'P': {
                                resL[resP]=0b1100001001101001;
                                resP++;
                                resL[resP]=0b1000000010000110;
                                resP++;
                                resL[resP]=0b10000101U|(intVals[input[i+4U]]<<13U);
                                resP++;
                                doMainInst=0;
                            }break; default: break;
                        }break; default: break;
                    }break; default: break;
                    
                }
                if(doMainInst){
                    res|=(uint16_t)opcode<<9U;
                    i+=1U;
                    uint16_t op0=intVals[input[i]];
                    i+=2U;
                    uint16_t op1=intVals[input[i]];
                    i+=2U;
                    printf("#%c",input[i]);
                    uint16_t jflag=(uint16_t)((uint16_t)input[i]==(uint8_t)'J');
                    res|=jflag<<8;
                    res|=op0<<4;
                    res|=op1;
                    printf("$%b,%b,%b,%b,%b,%b\n",target,opcode,jflag,op0,op1,res);
                    resL[resP]=res;
                    resP++;
                    printf("##############%s\n",input);
                    if((op0==11U)||(op1==11U)){
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
