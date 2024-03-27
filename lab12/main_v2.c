#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Глобальная переменная
int shared_variable = 0;

sem_t *semaphore;

// Функция потока
void *thread_function(void *arg) {
    for (int i = 1; i <= 5; ++i) {
        // Ожидаем разрешения на доступ к общей переменной
        sem_wait(semaphore);
        shared_variable++;
        pthread_t id = pthread_self();
        printf("Thread %ld: shared_variable: %d\n", id, shared_variable);
        
        // Освобождаем семафор для другого потока
        sem_post(semaphore);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    // Создаем и инициализируем семафоры
    semaphore = sem_open("/semaphore", O_CREAT, 0644, 1);
    
    if (semaphore == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread_function, NULL);
    pthread_create(&tid2, NULL, thread_function, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_close(semaphore);
    sem_unlink("/semaphore");
    return 0;
}
