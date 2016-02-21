#include <stdio.h>
#include <stdbool.h>

bool stage[5] = {true, true, true};

int reg1[20] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int reg2[20] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int reg3[20] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int lfsr_1() {
    if (stage[0]) {
        stage[0] = false;
        return reg1[0];
    }
    int n = 18, temp = reg1[6] ^reg1[17];   //1+x7+x18
    int k = 0;
    for (k = n - 1; k > 0; k--) reg1[k] = reg1[k - 1];
    reg1[0] = temp;
    return temp;
}

int lfsr_2() {
    if (stage[1]) {
        stage[1] = false;
        return reg2[0];
    }
    int n = 19, temp = reg2[0] ^reg2[1] ^reg2[4] ^reg2[18]; //1+x+x2+x5+x19
    int k = 0;
    for (k = n - 1; k > 0; k--) reg2[k] = reg2[k - 1];
    reg2[0] = temp;
    return temp;
}

int lfsr_3() {
    if (stage[2]) {
        stage[2] = false;
        return reg3[0];
    }
    int n = 20, temp = reg3[2] ^reg3[19];   //1+x3+x20
    int k = 0;
    for (k = n - 1; k > 0; k--) reg3[k] = reg3[k - 1];
    reg3[0] = temp;
    return temp;
}

