#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int vip_seats;
int total_vip;
int total_regular;
int regular_seats;
int total;
int total_customers;
int total_booked = 0;
typedef enum { VIP, REGULAR } CustomerType;

sem_t vip;
sem_t regular;
pthread_mutex_t booking_mutex = PTHREAD_MUTEX_INITIALIZER;

void *booking(void *arg) {
    int customer_id = *((int *)arg);
    CustomerType type = (customer_id <= 2) ? VIP : REGULAR;
    while (1) {
        pthread_mutex_lock(&booking_mutex);
        if (total_booked == total) {
            pthread_mutex_unlock(&booking_mutex);
            return NULL;
        }
        if (type == REGULAR && regular_seats == 0) {
            printf("Customer %d (Regular) cannot book. All Regular seats are booked.\n", customer_id);
            pthread_mutex_unlock(&booking_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&booking_mutex);

        if (type == VIP) {
            if (sem_trywait(&vip) == 0) {
                pthread_mutex_lock(&booking_mutex);
                printf("Customer %d (VIP) booked VIP seat %d.\n", customer_id, total_vip - vip_seats + 1);
                vip_seats--;
                total_booked++;
                pthread_mutex_unlock(&booking_mutex);
                return NULL;
            }
        }
        
        if (sem_trywait(&regular) == 0) {
            pthread_mutex_lock(&booking_mutex);
            printf("Customer %d (%s) booked Regular seat %d.\n", customer_id,(type == VIP) ? "VIP" : "Regular", total_regular - regular_seats + 1);
            regular_seats--;
            total_booked++;
            pthread_mutex_unlock(&booking_mutex);
            return NULL;
        }
        pthread_mutex_lock(&booking_mutex);
        if (total_booked == total) {
            pthread_mutex_unlock(&booking_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&booking_mutex);
    }
}

int main() {
    printf("Enter the total number of VIP seats: ");
    while (scanf("%d", &total_vip) != 1 || total_vip < 0) {
        printf("Invalid input! Please enter a non-negative number for VIP seats: ");
        while (getchar() != '\n');
    }
    printf("Enter the total number of Regular seats: ");
    while (scanf("%d", &total_regular) != 1 || total_regular < 0) {
        printf("Invalid input! Please enter a non-negative number for Regular seats: ");
        while (getchar() != '\n');
    }
    printf("Enter the total number of customers: ");
    while (scanf("%d", &total_customers) != 1 || total_customers < 0) {
        printf("Invalid input! Please enter a non-negative number for customers: ");
        while (getchar() != '\n'); 
    }
    vip_seats=total_vip;
    regular_seats=total_regular;
    total = vip_seats + regular_seats;
    pthread_t customers[total_customers];
    int customer_ids[total_customers];
    sem_init(&vip, 0, vip_seats);
    sem_init(&regular, 0, regular_seats);
    printf("Starting booking process...\n");
    for (int i = 0; i < total_customers; i++) {
        customer_ids[i] = i + 1;
        pthread_create(&customers[i], NULL, booking, &customer_ids[i]);
    }
    for (int i = 0; i < total_customers; i++) {
        pthread_join(customers[i], NULL);
    }
    sem_destroy(&vip);
    sem_destroy(&regular);
    pthread_mutex_destroy(&booking_mutex);
    printf("All seats booked. System exiting.\n");
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
