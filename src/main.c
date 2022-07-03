#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp) {
    char buffer[1024] = { 0 };
    int proc;
    siginfo_t child_info;

    proc = fork();

    if (proc == 0) {
        /* TODO: use exec */
        printf("Hello, World!\n");
        exit(69);
    }

    waitid(P_PID, proc, &child_info, WEXITED | WSTOPPED);

    if (child_info.si_status != 0)
        printf("\x1b[1;31mstatus %d\x1b[0m\n", child_info.si_status);

    return 0;
}
