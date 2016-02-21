#include <stdio.h>
#include "lfsr.h"

int main(int argc, char **argv) {
    int i = 0;
    for (i = 0; i < 10; i++) {
        putchar(lfsr_1() + 48);
    }
    puts("");
    for (i = 0; i < 10; i++) {
        putchar(lfsr_2() + 48);
    }
    puts("");
    for (i = 0; i < 10; i++) {
        putchar(lfsr_3() + 48);
    }
}

