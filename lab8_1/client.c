#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define FIFO_NAME1 "myfifo"
#define FIFO_NAME2 "myfifo2"

int main() {
    int fd_w, fd_r;
    char msg[256];

    // Открытие канала для записи
    fd_w = open(FIFO_NAME1, O_WRONLY);
    if (fd_w == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    fd_r = open(FIFO_NAME2, O_RDONLY);
    if (fd_r == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Клиент запущен. Введите сообщения:\n");

    // Ввод сообщений с клавиатуры и отправка в канал
    while (1) {
        fgets(msg, sizeof(msg), stdin);
        write(fd_w, msg, strlen(msg) - 1);

        if (read(fd_r, msg, sizeof(msg)) > 0) {
            printf("Получено сообщение от сервера: %s\n", msg);
        }
        else{
            printf("Ошибка при чтении сообщения\n");
            break;
        }
    }

    // Закрытие канала
    close(fd_w);
    close(fd_r);

    return 0;
}
