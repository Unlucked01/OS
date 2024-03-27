#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 1234
#define SEM_KEY 5678


void lock_sem(int sem_id) {
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1;
    sb.sem_flg = 0;

    if (semop(sem_id, &sb, 1) < 0) {
        perror("semop");
        exit(EXIT_FAILURE);
    }
}

void unlock_sem(int sem_id) {
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = 1;
    sb.sem_flg = 0;

    if (semop(sem_id, &sb, 1) < 0) {
        perror("semop");
        exit(EXIT_FAILURE);
    }
}

int create_sem(key_t key, int value) {
    int sem_id = semget(key, 1, IPC_CREAT | 0666);
    if (sem_id < 0) {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    unlock_sem(sem_id);
    return sem_id;
}

int main() {
    int shm_id, sem_id;
    int *shared_variable;
    pid_t pid;

    // Создание/получение разделяемой памяти
    shm_id = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Получение идентификатора семафора
    sem_id = create_sem(SEM_KEY, 1);

    // Присоединение разделяемой памяти к адресному пространству процесса
    shared_variable = (int *)shmat(shm_id, NULL, 0);
    if (shared_variable == (void *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Установка начального значения общей переменной
    *shared_variable = 0;

    // Создание дочернего процесса
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    if (pid == 0) {
        // Дочерний процесс
        for (int i = 1; i <= 10; i += 2) {
            lock_sem(sem_id);
            (*shared_variable)++;
            printf("%d\n", *shared_variable);
            unlock_sem(sem_id);
            sleep(1);
        }
    } else {
        // Родительский процесс
        for (int i = 2; i <= 10; i += 2) {
            lock_sem(sem_id);
            (*shared_variable)++;
            printf("%d\n", *shared_variable);
            unlock_sem(sem_id);
            sleep(1);
        }
        wait(NULL);
    }

    // Отсоединение разделяемой памяти от адресного пространства процесса
    shmdt(shared_variable);

    // Удаление разделяемой памяти и семафора
    shmctl(shm_id, 0, NULL);
    semctl(sem_id, 0, IPC_RMID);

    return 0;
}
