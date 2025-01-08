#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>

int numbers[100000];
int cleaned_numbers[100000];
int total= 0;
int cleaned_count = 0;
double mean = 0.0, median = 0.0, stddev = 0.0;
sem_t loading;
sem_t cleaning;
sem_t analysis;

void* loadingfunc(void* arg) {
    int fd = open("data.txt", O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char buffer[5000];
    int bytes_read, index = 0;
    char* token;
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        token = strtok(buffer, " \n");
        while (token != NULL) {
            numbers[index++] = atoi(token);
            token = strtok(NULL, " \n");
        }
    }
    total = index;
    close(fd);
    sem_post(&loading);
    return NULL;
}

void* cleaningfunc(void* arg) {
    sem_wait(&loading);
    int temp[100000], temp_count = 0;
    for (int i = 0; i < total; i++) {
        if (numbers[i] != -9999999) {
            temp[temp_count++] = numbers[i];
        }
    }
    int swap;
    for (int i = 0; i < temp_count - 1; i++) {
        for (int j = i + 1; j < temp_count; j++) {
            if (temp[i] > temp[j]) {
                swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
        }
    }
    cleaned_count = 0;
    for (int i = 0; i < temp_count; i++) {
        if (i == 0 || temp[i] != temp[i - 1]) {
            cleaned_numbers[cleaned_count++] = temp[i];
        }
    }
    sem_post(&cleaning);
    return NULL;
}

void* analysisfunc(void* arg) {
    sem_wait(&cleaning);
    double sum = 0.0;
    for (int i = 0; i < cleaned_count; i++) {
        sum += cleaned_numbers[i];
    }
    mean = sum / cleaned_count;
    if (cleaned_count % 2 == 0) {
        median = (cleaned_numbers[cleaned_count / 2 - 1] + cleaned_numbers[cleaned_count / 2]) / 2.0;
    } else {
        median = cleaned_numbers[cleaned_count / 2];
    }
    double variance = 0.0;
    for (int i = 0; i < cleaned_count; i++) {
        variance += pow(cleaned_numbers[i] - mean, 2);
    }
    stddev = sqrt(variance / cleaned_count);
    sem_post(&analysis); 
    return NULL;
}

void* reportingfunc(void* arg) {
    sem_wait(&analysis); 
    int fd = open("report.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening report file");
        exit(EXIT_FAILURE);
    }
    char report[5000];
    int offset = 0;
    offset += snprintf(report + offset, sizeof(report) - offset, "{\n");
    offset += snprintf(report + offset, sizeof(report) - offset, "  'Cleaned Data': [");
    for (int i = 0; i < cleaned_count; i++) {
        if (i > 0) {
            offset += snprintf(report + offset, sizeof(report) - offset, ", ");
        }
        offset += snprintf(report + offset, sizeof(report) - offset, "%d", cleaned_numbers[i]);
    }
    offset += snprintf(report + offset, sizeof(report) - offset, "],\n");
    offset += snprintf(report + offset, sizeof(report) - offset,"Mean: %.2f,\nMedian: %.2f,\nStandard Deviation: %.2f\n",mean, median, stddev);
    offset += snprintf(report + offset, sizeof(report) - offset, "}\n");
    write(fd, report, strlen(report));
    close(fd);
    return NULL;
}

int main() {
    pthread_t t1, t2, t3, t4;
    sem_init(&loading, 0, 0);
    sem_init(&cleaning, 0, 0);
    sem_init(&analysis, 0, 0);
    pthread_create(&t1, NULL, loadingfunc, NULL);
    pthread_create(&t2, NULL, cleaningfunc, NULL);
    pthread_create(&t3, NULL, analysisfunc, NULL);
    pthread_create(&t4, NULL, reportingfunc, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    printf("Report has generated successfully.\n");
    sem_destroy(&loading);
    sem_destroy(&cleaning);
    sem_destroy(&analysis);
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
