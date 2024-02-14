#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t sigset;
    if (sigemptyset(&sigset) == -1) {
        perror("sigemptyset");
        exit(EXIT_FAILURE);
    }

    if (sigismember(&sigset, SIGINT)) {
        printf("Сигнал SIGINT присутствует в сигнальной маске.\n");
        if (sigdelset(&sigset, SIGINT) == -1) {
            perror("sigdelset");
            exit(EXIT_FAILURE);
        }
        printf("Сигнал SIGINT был снят из сигнальной маски.\n");
    } else {
        printf("Сигнал SIGINT отсутствует в сигнальной маске.\n");
        if (sigaddset(&sigset, SIGINT) == -1) {
            perror("sigaddset");
            exit(EXIT_FAILURE);
        }
        printf("Сигнал SIGINT был установлен в сигнальной маске.\n");
    }

    return 0;
}