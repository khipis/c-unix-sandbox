#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

#define COMMAND_BUFFER 200
#define ARGUMENTS_COUNT 4
#define COMMAND_PROMPT "666:>"

void remove_newline(char *const *args_wsk, char *tmp, int args_count);

inline bool is_not_empty(const char *command);

__sighandler_t ctrl_z_exit();

void child_code(char *const *args_wsk);

void tokenize_command(char *command, char **args_wsk);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main(int argc, char **argv) {

    pid_t pid;

    char command[COMMAND_BUFFER];

    struct sigaction ctrlz;
    ctrlz.sa_handler = (__sighandler_t) ctrl_z_exit;
    sigemptyset(&ctrlz.sa_mask);
    ctrlz.sa_flags = 0;
    if (sigaction(SIGTSTP, &ctrlz, NULL) < 0) {
        perror("sigaction ctrl-z failure");
        return EXIT_FAILURE;
    }

    while (1) {
        char *args_wsk[ARGUMENTS_COUNT + 1] = {NULL, NULL, NULL, NULL, NULL, NULL};
        printf(COMMAND_PROMPT);

        fgets(command, COMMAND_BUFFER, stdin);

        if (is_not_empty(command)) {

            tokenize_command(command, args_wsk);

            pid = fork();
            if (pid == 0) { // Child
                child_code(args_wsk);
            }
            else if (pid > 0) { // Parent
                int ret;
                waitpid(pid, &ret, 0);
            }
            else {
                printf("Fork returned with error code %d", pid);
            }
        }

    }
    return EXIT_SUCCESS;
}
#pragma clang diagnostic pop

void tokenize_command(char *command, char **args_wsk) {
    char *tmp = strtok(command, " ,.");
    int args_count = 0;
    while (tmp != NULL) {
        args_wsk[args_count] = tmp;
        args_count = args_count + 1;
        tmp = strtok(NULL, " ");
        if (args_count > ARGUMENTS_COUNT) break;
    }

    remove_newline(args_wsk, tmp, args_count);
}

void child_code(char *const *args_wsk) {
    execvp(args_wsk[0], args_wsk);
    fprintf(stderr, "sHELL unknown command\n");
    exit(EXIT_FAILURE);
}

void remove_newline(char *const *args_wsk, char *tmp, int args_count) {
    tmp = args_wsk[args_count - 1];
    size_t last = strlen(tmp) - 1;
    tmp[last] = 0;
}

inline bool is_not_empty(const char *command) { return strlen(command) > 1; }

__sighandler_t ctrl_z_exit() {
    kill(0, SIGCONT);
    perror("sHELL Exit\n");
    exit(1);
}
