#include "z80.h"

struct z80Registers z80;

void z80Init(){
    mem_init();
    io_applyRom(mem_getPointer());
}

void z80Exec(unsigned char opcode){
    switch (opcode) {
        case 0x01: //ld bc,**
        case 0x11: //ld de,**
        case 0x21: //ld hl,**
        case 0x31: //ld sp,**
            z80Inst_ld_rr_v(opcode);
            break;
        case 0xA8: //xor b
        case 0xA9: //xor c
        case 0xAA: //xor d
        case 0xAB: //xor e
        case 0xAC: //xor h
        case 0xAD: //xor l
        //case 0xAE: //xor (hl) TODO
        case 0xAF: //xor a
            z80Inst_xor_a_r(opcode);
            break;
        case 0x32: //ldd (hl), a
            z80Inst_ldd_hl();
            break;
        default:
            fprintf(stderr, "Unknown OPCODE %X\n", opcode);
            return;
    }

    printf("OPCODE %2X\n", opcode);
    z80PrintRegisters();
}

unsigned char z80GetFlag(unsigned char flag){
    unsigned char value = z80.f / z80GetMaskForFlag(flag);

    return value;
}

void z80SetFlag(unsigned char flag, unsigned char value){
    if(value > 1){
        fprintf(stderr, "Invalid value for flag. Must be binary.");
        exit(EXIT_FAILURE);
    }

    unsigned char mask = z80GetMaskForFlag(flag);
    z80.f &= ~mask;
    z80.f |= value * z80GetMaskForFlag(flag);
}

unsigned char z80GetMaskForFlag(unsigned char flag){
    switch(flag){
        case 'z':
        case 'Z':
            return 0b10000000;
        break;
        case 'n':
        case 'N':
            return 0b01000000;
        break;
        case 'h':
        case 'H':
            return 0b00100000;
        break;
        case 'c':
        case 'C':
            return 0b00010000;
        break;
        default:
            fprintf(stderr, "Unknown flag");
            exit(EXIT_FAILURE);
        break;
    }
}

void z80Inst_ld_rr_v(unsigned char opcode){
    switch(opcode){
        //BC
        case 0x01:
            z80.c = io_readChar();
            z80.b = io_readChar();
        break;
        //DE
        case 0x11:
            z80.e = io_readChar();
            z80.d = io_readChar();
        break;
        //HL
        case 0x21:
            z80.l = io_readChar();
            z80.h = io_readChar();
        break;
        //SP
        case 0x31:{
            char c1 = io_readChar();
            char c2 = io_readChar();
            z80.sp = (c2 << 4) | c1;
        }
        break;
    }
}

void z80Inst_xor_a_r(unsigned char opcode){
    switch(opcode){
        case 0xA8: //xor b
            z80.a ^= z80.b;
        break;
        case 0xA9: //xor c
            z80.a ^= z80.c;
        break;
        case 0xAA: //xor d
            z80.a ^= z80.d;
        break;
        case 0xAB: //xor e
            z80.a ^= z80.e;
        break;
        case 0xAC: //xor h
            z80.a ^= z80.h;
        break;
        case 0xAD: //xor l
            z80.a ^= z80.l;
        break;
        case 0xAE: //xor (hl)
            //TODO
        break;
        case 0xAF: //xor a
            z80.a ^= z80.a;
        break;
    }
}

void z80Inst_ldd_hl(){
    char *mem = mem_getPointer();
    mem[z80.hl] = z80.a;
    z80.hl -= 1;
}

void z80PrintRegisters(){
    printf("A: %2X\t", z80.a);
    printf("F: %2X\t", z80.f);
    printf("B: %2X\t", z80.b);
    printf("C: %2X\t", z80.c);
    printf("D: %2X\t", z80.d);
    printf("E: %2X\t", z80.e);
    printf("H: %2X\t", z80.h);
    printf("L: %2X\t", z80.l);
    printf("SP: %2X\n", z80.sp);
    printf("Z: %2X\tN: %2X\tH: %2X\tC: %2X\n", z80GetFlag('z'), z80GetFlag('n')
           , z80GetFlag('h'), z80GetFlag('c'));
}






