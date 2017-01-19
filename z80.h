#include <stdlib.h>
#include <stdio.h>
#include "io.h"
#include "mem.h"

struct z80Registers{
    union{
        struct{
            //Flag Register
            /* bit  7 6 5 4 3 2 1 0 */
            /* flag Z N H C - - - - */
            unsigned char f;
            unsigned char a;
        };
        unsigned short af;
    };

    union{
        struct{
            unsigned char c;
            unsigned char b;
        };
        unsigned short bc;
    };

    union{
        struct{
            unsigned char e;
            unsigned char d;
        };
        unsigned short de;
    };

    union{
        struct{
            unsigned char l;
            unsigned char h;
        };
        unsigned short hl;
    };

    unsigned short sp, pc;
};

void z80Init();
void z80Exec(unsigned char opcode);
unsigned char z80GetFlag(unsigned char flag);
void z80SetFlag(unsigned char flag, unsigned char value);
unsigned char z80GetMaskForFlag(unsigned char flag);
void z80PrintRegisters();

/*
 * Loads value into register
 * OPCODES: 01 11 21 31
 * SIZE: 3 bytes
 * TIME: 10 cycles
 */
void z80Inst_ld_rr_v(unsigned char opcode);

/* >>>>> TODO: update flags <<<<<
 * XORS registers with register A
 * OPCODES: A8-AF
 * SIZE: 1 byte
 * TIME: 4 cycles (AE: 7 cycles)
 */
void z80Inst_xor_a_r(unsigned char opcode);

/*
 * Put A into memory address HL
 * OPCODES: 32
 * SIZE: 1 byte
 * TIME: 8 cycles
 */
void z80Inst_ldd_hl();








