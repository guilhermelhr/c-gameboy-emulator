#include <stdio.h>
#include "z80.h"
#include "io.h"

int main(int argc, char *argv[])
{
    io_readRom();
    z80Init();
    while(!io_isEoF()){
        z80Exec(io_readChar());
    }
    return 0;
}
