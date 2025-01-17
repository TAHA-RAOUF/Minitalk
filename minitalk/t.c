#include <stdio.h>
#include <unistd.h>
#include <sched.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0) {
        printf("Processus enfant : PID = %d\n", getpid());
    } else {
        printf("Processus parent : PID = %d\n", getppid());
    }

    return 0;
}

