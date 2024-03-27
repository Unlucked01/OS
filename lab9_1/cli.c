#include <stdio.h>
#include <stdlib.h>
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

    msgid = msgget(key, 0664);
    if (msgid == -1) {
        perror("Error accessing message queue");
        exit(EXIT_FAILURE);
    }

	for(;;) {
		msgrcv(msgid, &message, sizeof(message.mtext), 1, 0);
		printf("Client received: %d\n", atoi(message.mtext));	
	}

    return 0;
}
