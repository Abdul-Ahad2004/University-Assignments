#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
int execute(const char *stage) 
{
    printf("Starting %s\n", stage);
    sleep(2);
    if (rand() % 100 < 15) 
    {
        printf("%s failed!\n", stage);
        return 1;
    }
    return 0;
}

int run(const char *stage) 
{
    int retries = 0;
    int status;
    while (retries < 3) 
    {
        status = execute(stage);
        if (status == 0) {
            return 0;
        }
        retries++;
        printf("Retrying %s %d time\n", stage, retries);
    }
    printf("%s failed after 3 attempts.\n", stage);
    return 1;
}

int main() 
{
    const char *stages[] = {"System Update","Software Installation","Configuration Setup","Security Checks"};
    int i;
    for (i = 0; i < 4; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
        {  
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        { 
            srand(time(0));
            int result = run(stages[i]);
            exit(result);
        } 
        else 
        {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            {
                printf("%s finished successfully.\n\n", stages[i]);
            } 
            else 
            {
                printf("Aborting deployment!!\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    printf("Deployment completed successfully!\n");
    return 0;
}

