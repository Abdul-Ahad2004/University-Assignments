#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
void tokenize(char *input, char **args) {
    char *token;
    int index = 0;
    token = strtok(input, " \n");
    while (token != NULL) {
        args[index++] = token;
        token = strtok(NULL, " \n");
    }
    args[index] = NULL;
}

int main() {
    char input[100];
    char *args[10];
    pid_t pid;
    int status;
    printf("Welcome to the Custom shell!!\n");
    while (1) {
        printf("q1> ");
        fflush(stdout);
        ssize_t bytes_read = read(1, input, 256);
        if (bytes_read < 0) 
        {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
        input[bytes_read] = '\0';
        if (strcmp(input, "exit\n") == 0)
        {
            printf("\nExiting  Custom shell!!\n");
            break;
        }
        tokenize(input, args);
        if (strcmp(args[0], "cd") == 0) 
        {
            if (args[1] == NULL) 
            {
                fprintf(stderr, "cd: expected argument to \"cd\"\n");
            } 
            else
            {
                if (chdir(args[1]) != 0)
                {
                    perror("cd failed");
                }
            }
            continue;
        }
        pid = fork();
        if (pid < 0) 
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        } 
        else if (pid == 0) 
        { 
            if (execvp(args[0], args) == -1) 
            {
                perror("exec failed");
            }
            exit(EXIT_FAILURE);
        } 
        else 
        { 
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

