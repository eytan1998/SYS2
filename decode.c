#include "stdio.h"
#include <dlfcn.h>
#include <string.h>


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage : decode <codec> <message>\n");
        return -1;
    }


    void *handle;
    void (*func_encode)(char *);

    if (strcmp(argv[1], "codecA") == 0) {
        handle = dlopen("./libcodecA.so", RTLD_LAZY);
    } else if (strcmp(argv[1], "codecB") == 0) {
        handle = dlopen("./libcodecB.so", RTLD_LAZY);
    } else {
        printf("Usage : decode <codec> <message>\n");
        return -1;
    }
    if (!handle) {
        // fail to load the library
        return -1;
    }
    func_encode = dlsym(handle, "decode");
    func_encode(argv[2]);
    printf("%s\n", argv[2]);
    dlclose(handle);

    return 0;
}