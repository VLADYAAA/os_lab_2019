#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <array_size> <seed>\n", argv[0]);
        printf("Example: %s 1000000 123\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Дочерний процесс - запускаем sequential_min_max через exec
        printf("Child process (PID: %d) launching sequential_min_max...\n", getpid());
        
        // Вариант 1: execl - передача аргументов по списку
        execl("./sequential_min_max", "sequential_min_max", argv[1], argv[2], NULL);
        
        // Вариант 2: execv - передача аргументов через массив
        // char *args[] = {"sequential_min_max", argv[1], argv[2], NULL};
        // execv("./sequential_min_max", args);
        
        // Если exec вернул управление, значит произошла ошибка
        perror("exec failed");
        exit(1);
    }
    else {
        // Родительский процесс
        printf("Parent process (PID: %d) started child (PID: %d)\n", getpid(), pid);
        printf("Waiting for child process to complete...\n");
        
        int status;
        waitpid(pid, &status, 0);
        
        printf("\nChild process finished\n");
        
        if (WIFEXITED(status)) {
            printf("Child exited normally with status: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child terminated by signal: %d\n", WTERMSIG(status));
        }
        
        return 0;
    }
}