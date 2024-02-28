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
    int fd_r, fd_w;
    char msg[256];

    // Создание именованного канала, если он еще не существует
    mkfifo(FIFO_NAME1, 0666);
    mkfifo(FIFO_NAME2, 0666);

    // Открытие канала для чтения
    fd_r = open(FIFO_NAME1, O_RDONLY);
    if (fd_r == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    fd_w = open(FIFO_NAME2, O_WRONLY);
    if (fd_w == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Сервер запущен. Ожидание сообщений...\n");

    // Чтение сообщений из канала и вывод на экран
    while (1) {
        if (read(fd_r, msg, sizeof(msg)) > 0) {
            printf("Получено сообщение от клиента: %s\n", msg);
            // Отправляем сообщение обратно клиенту
            write(fd_w, msg, strlen(msg) - 1);
        }
        else {
            printf("Ошибка при чтении сообщения\n");
            break;
        }
    }

    // Закрытие канала
    close(fd_r);
    close(fd_w);
    unlink(FIFO_NAME1);
    unlink(FIFO_NAME2);

    return 0;
}
