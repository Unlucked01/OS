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

    // Создание именованного канала
    mkfifo(FIFO_NAME, 0666);

    // Открытие канала для чтения
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Сервер запущен. Ожидание сообщений...\n");

    // Чтение сообщений из канала и вывод на экран
    while (1) {
        if (read(fd, msg, sizeof(msg)) > 0) {
            printf("Получено сообщение от клиента: %s\n", msg);
        }
    }

    // Закрытие канала
    close(fd);
    unlink(FIFO_NAME);

    return 0;
}
