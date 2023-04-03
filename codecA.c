#include "string.h"

void encode(char *input) {
    for (int i = 0; i < strlen(input); ++i) {
        char c = input[i];
        if (c >= 'a' && c <= 'z') {
            c -= 'a' - 'A';
        } else if (c >= 'A' && c <= 'Z') {
            c += 'a' - 'A';
        }
        input[i] = c;
    }
}

void decode(char *input) {
    for (int i = 0; i < strlen(input); ++i) {
        char c = input[i];
        if (c >= 'a' && c <= 'z') {
            c -= 'a' - 'A';
        } else if (c >= 'A' && c <= 'Z') {
            c += 'a' - 'A';
        }
        input[i] = c;
    }
}