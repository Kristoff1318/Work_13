#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

static void sighandler(int signo) {
    if (signo == SIGINT) {
        printf("\nSIGINT exit.\n");

        int f;
        f = open("exit", O_APPEND | O_WRONLY | O_CREAT, 0644);
		char m[] = "Exit due to SIGINT.\n";
		write(f, m, strlen(m));
        close(f);
		exit(0);
    }

    if (signo == SIGUSR1) printf("\nSIGUSR1. Parent PID: %d\n", getppid());
}

int main() {
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);

    while (1) {
        printf("PID: %d\n", getpid());
        sleep(1);
    }

    return 0;
}
