
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <fcntl.h>

#define WRITE 1
#define READ 0


int main() {
    //for receive commends
    int i;
    char *argv[10];
    char command[1024];
    char *token;

    while (1) {
        //ignore crl+C
        signal(SIGINT, SIG_IGN);

        //TODO ignore crl+C
        printf("<StShell>: ");
        fgets(command, 1024, stdin);
        if(strlen(command)<=1) continue;
        command[strlen(command) - 1] = '\0'; // replace \n with \0


        //stop if it gets exit
        if (!strcmp(command, "exit")) {

            return 0;
        }

        /* parse command line if got pipes*/
        char *pip1 = strtok(command, "|");
        char *pip2 = strtok(NULL, "|");
        char *pip3 = strtok(NULL, "|");

        //create pipes and see if error
        int fd1[2];
        int fd2[2];
        int err = 0;
        err += pipe(fd1);
        err += pipe(fd2);
        if (err > 0) {
            printf("cant open pipes");
            return 1;
        }

        if (pip1 == NULL)
            return 0;

        if (!fork()) {
            //TODO NOT ignore crl+C

            if (!fork()) {
                if (!fork()) {

                    i = 0;
                    token = strtok(pip3, " ");
                    while (token != NULL) {
                        argv[i] = token;
                        token = strtok(NULL, " ");
                        i++;
                    }
                    argv[i] = NULL;
                    if (pip3 != NULL) {
                        if (i > 2) {
                            if (strcmp(argv[i - 2], ">>") == 0) {
                                int fd = open(argv[i - 1], O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
                                dup2(fd, STDOUT_FILENO);
                                close(fd);
                                argv[i - 2] = NULL;

                            } else if (strcmp(argv[i - 2], ">") == 0) {
                                int fd = open(argv[i - 1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
                                printf("%d\n", fd);
                                dup2(fd, STDOUT_FILENO);
                                close(fd);
                                argv[i - 2] = NULL;

                            }
                        }

                        close(fd1[WRITE]);
                        close(fd1[READ]);
                        close(fd2[WRITE]);
                        dup2(fd2[READ], STDIN_FILENO);
                        close(fd2[READ]);
                        execvp(argv[0], argv);
                    }
                    close(fd1[READ]);
                    close(fd1[WRITE]);
                    close(fd2[READ]);
                    close(fd2[WRITE]);
                    wait(NULL);
                    exit(0);

                }

                //parse the second part
                i = 0;
                token = strtok(pip2, " ");
                while (token != NULL) {
                    argv[i] = token;
                    token = strtok(NULL, " ");
                    i++;
                }
                argv[i] = NULL;
                //check if there is command to exec
                if (pip2 != NULL) {
                    close(fd1[WRITE]);
                    dup2(fd1[READ], STDIN_FILENO);
                    close(fd1[READ]);

                    //check if you need to do more pipe
                    if (pip3 != NULL) {
                        close(fd2[READ]);
                        dup2(fd2[WRITE], STDOUT_FILENO);
                        close(fd2[WRITE]);

                    } else if (i > 2) {//if no more pip -> check if >>
                        if (strcmp(argv[i - 2], ">>") == 0) {
                            int fd = open(argv[i - 1], O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
                            dup2(fd, STDOUT_FILENO);
                            close(fd);
                            argv[i - 2] = NULL;
                        } else if (strcmp(argv[i - 2], ">") == 0) {
                            int fd = open(argv[i - 1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
                            dup2(fd, STDOUT_FILENO);
                            close(fd);
                            argv[i - 2] = NULL;
                        }

                    }
                    execvp(argv[0], argv);

                }
                close(fd1[READ]);
                close(fd1[WRITE]);
                close(fd2[READ]);
                close(fd2[WRITE]);

                wait(NULL);
                exit(0);

            }
            i = 0;
            token = strtok(pip1, " ");

            while (token != NULL) {
                argv[i] = token;
                token = strtok(NULL, " ");
                i++;
            }
            argv[i] = NULL;
            if (pip2 != NULL) {
                close(fd1[READ]);
                dup2(fd1[WRITE], STDOUT_FILENO);
                close(fd1[WRITE]);
            } else if (i > 2) {
                if (strcmp(argv[i - 2], ">>") == 0) {
                    int fd = open(argv[i - 1], O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    argv[i - 2] = NULL;

                } else if (strcmp(argv[i - 2], ">") == 0) {
                    int fd = open(argv[i - 1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    argv[i - 2] = NULL;
                }
            }
            execvp(argv[0], argv);
            close(fd1[READ]);
            close(fd1[WRITE]);
            close(fd2[READ]);
            close(fd2[WRITE]);
            wait(NULL);
            exit(0);

        }
        close(fd1[READ]);
        close(fd1[WRITE]);
        close(fd2[READ]);
        close(fd2[WRITE]);
        wait(NULL);

    }
}