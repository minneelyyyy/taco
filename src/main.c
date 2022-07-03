#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define COL_RED     "\x1b[1;31m"
#define COL_RESET   "\x1b[0m"

int main(int argc, char **argv, char **envp) {
    char buffer[1024] = { 0 };
    int proc;
    siginfo_t child_info;

    for (;;) {
        printf("$ ");
        fgets(buffer, 1024, stdin);

        /* handle shell specific commands */
        if (strcmp(buffer, "exit\n") == 0) {
            break;
        }

        proc = fork();

        if (proc == 0) {
            /* system() relies on sh being the shell, this means
             * taco does not yet work as a stand-alone shell */
            exit(system(buffer));
        }

        waitid(P_PID, proc, &child_info, WEXITED | WSTOPPED);

        if (child_info.si_status != 0)
            printf(COL_RED "status %d" COL_RESET "\n", child_info.si_status);
    }

    return 0;
}
