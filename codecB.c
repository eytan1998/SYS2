#include "string.h"


void encode(char * input) {
    for (int i = 0; i < strlen(input); ++i) {
        input[i] += 3;
    }
}
void decode(char * input){
    for (int i = 0; i < strlen(input); ++i) {
        input[i] -= 3;
    }
}