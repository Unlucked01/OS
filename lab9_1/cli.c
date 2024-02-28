#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define MSG_SIZE 256

struct msg_buffer {
    long msg_type;
    int msg_text;
};

int main() {
    key_t key = ftok("oslab3server.out", 0);

	if (key == (key_t)-1)
		return 2;

	int queue = msgget(key, IPC_CREAT | 0600);

	if (queue == -1)
		return 3;

	struct msg_buffer msg;
	msg.msg_text = 1;

	for (;;) {
		sleep(1);

		if (msgsnd(queue, &msg, 0, 0) == -1)
			return 4;

		if (msgrcv(queue, &msg, sizeof(msg.msg_text), 0, 0) == -1)
			return 5;

		printf("Number of users in system: %i\n", msg.msg_text);
	}

	return 0;
}