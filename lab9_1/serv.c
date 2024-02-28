#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

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
	char buf[32];
	FILE* pipe;

	msg.msg_type = 1;

	for (;;) {
		if (msgrcv(queue, &msg, 0, 0, 0) == -1) 
			return 4;

		pipe = popen("who | wc -l", "r");

		if (pipe == NULL)
			return 5;

		if (fgets(buf, sizeof(buf), pipe) == NULL)
			return 6;

		if (pclose(pipe))
			return 8;

		msg.msg_text = atoi(buf);

		if (msgsnd(queue, &msg, sizeof(msg.msg_text), 0) == -1)
			return 9;
	}

	return 0;
}