#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>
#define MAX 200
void decrypt(const char *input, char *output) 
{
    int i;
    for (i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) 
        {
            if (input[i] == 'A') output[i] = 'Z';
            else if (input[i] == 'a') output[i] = 'z';
            else output[i] = input[i] - 1;
        }
        else 
        {
            output[i] = input[i];
        }
    }
    output[i] = '\0'; 
}

void redact(const char *input, char *output) 
{
    strcpy(output, input);
    char *credit = strstr(output, "Credit Card:");
    if (credit != NULL)
    {
        credit += strlen("Credit Card: ");
        strncpy(credit, "[REDACTED]",strlen(input) - strlen("Credit Card: "));
    }
    char *email = strstr(output, "email:");
    if (email != NULL) 
    {
        email += strlen("email: ");
        strncpy(email, "[REDACTED]", strlen(input) - strlen("email: "));
    }
}

int main() 
{
    char input_file[256], output_file[256];
    int choice;
    printf("Enter input file name: ");
    scanf("%s", input_file);
    printf("Enter output file name: ");
    scanf("%s", output_file);
    while (1) 
    {
        printf("Choose transformation method:\n");
        printf("1. Decrypt Data\n");
        printf("2. Redact Sensitive Information\n");
        printf("Enter your choice (1 or 2): ");
        scanf("%d", &choice);
        if (choice == 1 || choice == 2) 
        {
            break;
        }
        else 
        {
            printf("You entered an invalid choice!!\n");
        }
    }
    int input_fd = open(input_file, O_RDONLY);
    if (input_fd == -1) 
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
    int pipefd[2];
    if (pipe(pipefd) == -1) 
    {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid < 0) 
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) 
    { 
        close(pipefd[0]);
        char line[MAX];
        char transformed_line[MAX];
        ssize_t bytes_read;
        bytes_read = read(input_fd, line, MAX);
        line[bytes_read] = '\0';
        if (choice == 1) 
        {
            decrypt(line, transformed_line);
        } 
        else 
        {
            redact(line, transformed_line);
        }
        write(pipefd[1], transformed_line, strlen(transformed_line));
        close(pipefd[1]);
        close(input_fd);
        exit(0);
    } 
    else 
    {  
        close(pipefd[1]);
        wait(NULL);
        int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (output_fd == -1) 
        {
            perror("Error opening output file");
            exit(EXIT_FAILURE);
        }
        char buffer[MAX];
        ssize_t length;
        length = read(pipefd[0], buffer,MAX);
        buffer[length] = '\0'; 
        write(output_fd, buffer, length);
        close(pipefd[0]);
        close(output_fd); 
        printf("Data transformation completed successfully.\n");
        if (choice == 1) 
        {
            printf("Decryption applied.\n");
        } 
        else if (choice == 2)
        {
            printf("Sensitive data redacted.\n");
        }
    }
    return 0;
}

