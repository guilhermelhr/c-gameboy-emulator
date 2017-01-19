#include <stdlib.h>

struct MemMap{
    union{
        struct{
                                    //starting address
            char rom[0x4000];       //0000
            char srom[0x4000];      //4000
            char vram[0x4000];      //8000
            char sram[0x2000];      //A000
            char ram[0x2000];       //C000
            char eram[0x2000];      //E000
            char sprtmem[0x1E00];   //FE00
            char io0[0x00A0];       //FEA0
            char io1[0x0060];       //FF00
            char io2[0x004C];       //FF4C
            char iram[0x0034];      //FF80
            char ier;               //FFFF
        };
        char mem[0xFFFF];
    };
};

void mem_init();
char * mem_getPointer();
struct MemMap * mem_getMap();
