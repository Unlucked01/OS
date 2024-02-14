#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int signum) {
    printf("Прошло 5 секунд. Продолжить работу? (y/n): ");
}

int main() {
    signal(SIGALRM, alarm_handler);

    while (1) {
        alarm(5);
        pause();
        char response;
        scanf(" %c", &response);

        if (response == 'n' || response == 'N') {
            printf("Программа завершена.\n");
            break;
        }
    }
    return 0;
}
