#include "stdio.h"
#include "string.h"

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 4) {// != 3 or 4
        printf("usage:  cmp <file1> <file2> -v\n");
        return 1;

    }
    if (argc == 4 && strcmp(argv[3], "-v") != 0) {
        printf("usage:  cmp <file1> <file2> -v\n");
        return 1;
    }
    // if used -v
    int isVerbose = FALSE;
    if (argc == 4) isVerbose = TRUE;

    int result = strcmp(argv[1], argv[2]);

    if (isVerbose) {
        if (result) {// != 0 different
            printf("distinct %d\n", result);

        } else {
            printf("equal\n");

        }
    }
    return (result == 0) ? result : 1;
}