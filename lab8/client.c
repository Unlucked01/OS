#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_NAME "myfifo"

int main() {
    int fd;
    char msg[256];

    // Открытие канала для записи
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Клиент запущен. Введите сообщения:\n");

    // Ввод сообщений с клавиатуры и отправка в канал
    while (1) {
        fgets(msg, sizeof(msg), stdin);
        write(fd, msg, sizeof(msg));
    }

    // Закрытие канала
    close(fd);

    return 0;
}
