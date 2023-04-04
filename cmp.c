#include "stdio.h"
#include "string.h"

#define TRUE 1
#define FALSE 0

char toLower(char input) {
    if (input >= 'A' && input <= 'Z') {
        input += 'a' - 'A';
    }
    return input;
}

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 5) {// != 3 or 4
        printf("usage:  cmp <file1> <file2> -v\n");
        return 1;
    }
    // if used -v
    int isVerbose = FALSE;

    // if used -i
    int isIgnore = FALSE;


    if (argc == 4) {
        if (strcmp(argv[3], "-v") == 0) {
            isVerbose = TRUE;
        } else if (strcmp(argv[3], "-i") == 0) {
            isIgnore = TRUE;
        } else {
            printf("usage:  cmp <file1> <file2> -v\n");
            return 1;
        }
    }
    if (argc == 5) {
        if ((strcmp(argv[3], "-v") == 0 && strcmp(argv[4], "-i") == 0) ||
            (strcmp(argv[4], "-v") == 0 && strcmp(argv[3], "-i") == 0)) {
            isVerbose = TRUE;
            isIgnore = TRUE;
        } else {//both not true
            printf("usage:  cmp <file1> <file2> -v\n");
            return 1;
        }
    }

    //open file1
    FILE *fp1 = fopen(argv[1], "r");
    if (fp1 == NULL) {//not exist
//        if (isVerbose)
//            printf("target file1 not exist\n");
        return 1;
    }
    //open file2
    FILE *fp2 = fopen(argv[2], "r");
    if (fp2 == NULL) {//not exist
        fclose(fp1);
//        if (isVerbose)
//            printf("target file1 not exist\n");
        return 1;
    }

    int isEquals = FALSE;

    char c1;
    char c2;
    while (TRUE) {
        c1 = getc(fp1);
        c2 = getc(fp2);
        if (c1 == EOF && c2 == EOF) {
            isEquals = TRUE;
            break;
        } else if (c1 != EOF && c2 != EOF) {
            if (isIgnore) {
                c1 = toLower(c1);
                c2 = toLower(c2);
            }
            if (c1 != c2) break;

        } else {//if one finish and other not
            break;
        }
    }
    if (isVerbose) {
        if (isEquals) {
            printf("equal\n");
        } else {
            printf("distinct\n");

        }
    }
    return (isEquals) ? 0 : 1;
}