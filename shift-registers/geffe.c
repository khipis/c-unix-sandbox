#include <stdio.h>
#include <stdbool.h>
#include "lfsr.h"

int geffe() {
    int lf1 = lfsr_1();
    int lf2 = lfsr_2();
    int lf3 = lfsr_3();
    int and1 = lf1 & lf2;
    int and2;
    if (lf2 == 1) and2 = 0 & lf3;
    else and2 = 1 & lf3;
    return and1 ^ and2;
}

int main(int argc, char **argv) {
    int i = 0;
    for (i = 0; i < 100; i++) {
        putchar(geffe() + 48);
    }
}

