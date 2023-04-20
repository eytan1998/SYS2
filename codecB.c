#include "string.h"

#define ASCII_LEN 256

void encode(char *input) {
    for (int i = 0; i < strlen(input); ++i) {
        if ((int) input[i] +3  >= 256) input[i] -= ASCII_LEN;
        input[i] += 3;
    }
}

void decode(char *input) {
    for (int i = 0; i < strlen(input); ++i) {
        if ((int) input[i] - 3 < 0) input[i] += ASCII_LEN;
        input[i] -= 3;
    }

}