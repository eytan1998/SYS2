
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

int main() {
    signal(SIGINT, SIG_IGN);
    int i;
    char *argv[10];
    char command[1024];
    char *token;

    while (1) {
        fgets(command, 1024, stdin);
        command[strlen(command) - 1] = '\0'; // replace \n with \0

        if (!strcmp(command,"exit")){
            return 0;
        }
        /* parse command line */
        i = 0;
        token = strtok(command, " ");
        while (token != NULL) {
            argv[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        argv[i] = NULL;

        /* Is command empty */
        if (argv[0] == NULL)
            continue;

        /* for commands not part of the shell command language */
        if (fork() == 0) {
            //so kid died with Crl+C
            signal(SIGINT,  SIGEV_SIGNAL);
            execvp(argv[0], argv);
            wait(NULL);
        }
    }
    return 0;
}