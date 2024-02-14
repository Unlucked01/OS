#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void redirect_output() {
    freopen("output.txt", "a", stdout);
}

int main() {
    if (fork() == 0) {
        printf("child\nPID: %d, PPID: %d\n", getpid(), getppid());
        redirect_output();
        execlp("ps", "ps", NULL);
    } else {
        printf("parent\nPID: %d, PPID: %d\n", getpid(), getppid());
        sleep(1);
        redirect_output();
        execlp("ps", "ps", NULL); 
        wait(NULL);
    }
    return 0;
}
