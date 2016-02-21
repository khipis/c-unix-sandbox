#include <stdio.h>
#include <stdbool.h>
#include "lfsr.h"

int shrinker() {
    int lf1 = lfsr_1();
    int lf2 = lfsr_2();

    while (lf1 != 1) {
        lf1 = lfsr_1();
        lf2 = lfsr_2();
    }
    return lf2;
}

int main(int argc, char **argv) {
    int i = 0;
    for (i = 0; i < 100; i++) {
        putchar(shrinker() + 48);
    }
}

