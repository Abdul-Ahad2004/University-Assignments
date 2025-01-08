#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <errno.h>

#define SEM_KEY 1234
#define SHM_KEY 5678

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}
int main(int argc, char *argv[]) {
    char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        error("Error opening file");
    }
    int shmid = shmget(SHM_KEY, 21, IPC_CREAT | 0666);
    if (shmid == -1) {
        error("shmget failed");
    }
    char *shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        error("shmat failed");
    }
    int semid = semget(SEM_KEY, 2, IPC_CREAT | 0666);
    if (semid == -1) {
        error("semget failed");
    }
    if (semctl(semid, 0, SETVAL, 1) == -1) error("semctl SETVAL failed for producer semaphore");
    if (semctl(semid, 1, SETVAL, 0) == -1) error("semctl SETVAL failed for consumer semaphore");

    struct sembuf sem_wait = {0, -1, 0};
    struct sembuf sem_signal = {0, 1, 0}; 

    char buffer[20];
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, 20)) > 0) {
        printf("[Producer] Read %ld bytes from file\n", bytes_read);
        sem_wait.sem_num = 0; 
        if (semop(semid, &sem_wait, 1) == -1) {
            error("semop wait failed");
        }
        memcpy(shared_memory, buffer, bytes_read);
        shared_memory[bytes_read] = '\0';
        printf("[Producer] Written to shared memory: %s\n", shared_memory);
        sem_signal.sem_num = 1;
        if (semop(semid, &sem_signal, 1) == -1) {
            error("semop signal failed");
        }
    }
    sem_wait.sem_num = 0;
    if (semop(semid, &sem_wait, 1) == -1) {
        error("semop wait failed");
    }
    strcpy(shared_memory, "$");
    sem_signal.sem_num = 1;
    if (semop(semid, &sem_signal, 1) == -1) {
        error("semop signal failed");
    }
    shmdt(shared_memory);
    close(fd);
    printf("[Producer] Completed.\n");
    return 0;
}


//pid_t pid;
//    char buffer[1024];
//    ssize_t bytes_read;//
//    if (pipe(pipefd) == -1) {
//        perror("pipe");
//        exit(1);
//    }

//    pid = fork();

//    if (pid < 0) {
//        perror("fork");
//        exit(1);
//    }

//    if (pid > 0) {
//        close(pipefd[0]);
//        int src_fd = open(argv[1], O_RDONLY);
//        if (src_fd < 0) {
//            perror("open source file");
//            exit(1);
//        }
//        while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
//            write(pipefd[1], &bytes_read, sizeof(bytes_read));
//            write(pipefd[1], buffer, bytes_read);
//        }
//        close(src_fd);
//        close(pipefd[1]);
//        wait(NULL);
//    } else {
//        close(pipefd[1]);
//        int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//        if (dest_fd < 0) {
//            perror("open destination file");
//            exit(1);//
//        }
