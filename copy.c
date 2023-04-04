
#include "stdio.h"
#include "string.h"

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 5) {// != 3 or 4
        printf("usage:  copy <file1> <file2> -v\n");
        return 1;
    }
    // if used -v
    int isVerbose = FALSE;

    // if used -f
    int isForce = FALSE;


    if (argc == 4) {
        if (strcmp(argv[3], "-v") == 0) {
            isVerbose = TRUE;
        } else if (strcmp(argv[3], "-f") == 0) {
            isForce = TRUE;
        } else {
            printf("usage:  copy <file1> <file2> -v\n");
            return 1;
        }
    }
    if (argc == 5) {
        if ((strcmp(argv[3], "-v") == 0 && strcmp(argv[4], "-f") == 0) ||
            (strcmp(argv[4], "-v") == 0 && strcmp(argv[3], "-f") == 0)) {
            isVerbose = TRUE;
            isForce = TRUE;
        } else {//both not true
            printf("usage:  copy <file1> <file2> -v\n");
            return 1;
        }
    }

    //see if dest exist
    FILE *fp = fopen(argv[2], "r");
    if (fp != NULL) {//exist
        if (!isForce) { // do not override
            if (isVerbose)
                printf("target file exist\n");
            fclose(fp);
            return 1;
        }
        fclose(fp);
    }


    //open src
    FILE *fsrc = fopen(argv[1], "r");
    if (fsrc == NULL) {//not exist
        if (isVerbose)
            printf("general failure\n");
        return 1;
    }

    //open dst
    FILE *fdst = fopen(argv[2], "w");
    if (fdst == NULL) {//cant open
        if (isVerbose)
            printf("general failure\n");

        fclose(fsrc);
        return 1;
    }

    int isError = FALSE;
    //transfer
    int c;
    while ((c = getc(fsrc)) != EOF) {
        if (c == 0) {// equals null
            isError = TRUE;
            break;
        }
        putc(c, fdst);
    }

    fclose(fsrc);
    fclose(fdst);

    if (isVerbose && isError)
        printf("general failure\n");
    if (isVerbose && !isError)
        printf("success\n");

    return isError;
}