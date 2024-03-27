#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msgbuf {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key;
    int msgid;
    struct msgbuf message;

    key = ftok("server.c", 'A');

    msgid = msgget(key, 0664 | IPC_CREAT);
    if (msgid == -1) {
        perror("Error creating message queue");
        exit(EXIT_FAILURE);
    }

    for (;;) {
        FILE* pipe = popen("who | wc -l", "r");

        fgets(message.mtext, sizeof(message.mtext), pipe);
        
        message.mtype = 1;
        msgsnd(msgid, &message, sizeof(message.mtext), 0);
        printf("Server sent: %d\n", atoi(message.mtext));
        
        sleep(3);
    }
	
    return 0;
}
