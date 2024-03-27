#include <stdio.h>
#include <pthread.h>

// Глобальная переменная
int var = 1;

// Функция, которую будут выполнять потоки
void *thread_function(void *arg) {
    int *increment_value = (int *)arg;
    printf("Before increment in thread: %d\n", var);
    var += *increment_value;
    printf("After increment in thread: %d\n", var);

    pthread_exit(NULL);
}

int main() {
    printf("Before branching: %d\n", var);

    var++;
    printf("After increment before branching: %d\n\n", var);

    // Создание и запуск первого потока
    pthread_t tid1;
    int increment_value1 = 3;
    pthread_create(&tid1, NULL, thread_function, (void *)&increment_value1);

    // Создание и запуск второго потока
    pthread_t tid2;
    int increment_value2 = 5;
    pthread_create(&tid2, NULL, thread_function, (void *)&increment_value2);

    // Ожидание завершения работы потоков
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Вывод значения переменной после завершения работы потоков
    printf("After joining threads: %d\n", var);

    return 0;
}
