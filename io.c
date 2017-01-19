#include "io.h"

char rom[ROM_SIZE + 1];
unsigned int p = 0;

char io_readChar(){
    return rom[p++];
}

int io_isEoF(){
    return p >= ROM_SIZE;
}

void io_readRom(){
    FILE *romFile = fopen("roms\\DMG_ROM.bin", "rb");
    if(romFile != NULL){
        fread(rom, 1, ROM_SIZE, romFile);
    }else{
        printf("file not found\n");
        exit(1);
    }

    /*for(int i = 0; i < ROM_SIZE; i++){
        printf("%d ", rom[i]);
    }

    printf("\n");*/
}


void io_applyRom(char *mem){
    memcpy(mem, rom, ROM_SIZE);
}
