#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROM_SIZE 256

char io_readChar();
int io_isEoF();
void io_readRom();
void io_applyRom(char *mem);
