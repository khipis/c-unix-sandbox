#include <stdio.h>
#include "lfsr.h"

int stop_and_go() {
    int lf2, lf3;
    if (lfsr_1() == 1) {
        lf2 = lfsr_2();
        lf3 = reg3[0];
    }
    else {
        lf3 = lfsr_3();
        lf2 = reg2[0];
    }
    return lf2 ^ lf3;
}


int main(int argc, char **argv) {
    int i = 0;
    for (i = 0; i < 100; i++) {
        putchar(stop_and_go() + 48);
    }
}

