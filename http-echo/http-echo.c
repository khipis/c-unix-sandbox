#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 8096

int http_echo(int listen_fd, int socket_fd);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

int main(int argc, char **argv) {
    int pid, listen_fd, socket_fd;
    socklen_t length;
    static struct sockaddr_in cli_addr;
    static struct sockaddr_in serv_addr;

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("system call socket");
        EXIT_FAILURE;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(80);

    if (bind(listen_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("system call bind");
        EXIT_FAILURE;
    }
    if (listen(listen_fd, 64) < 0) {
        perror("system call listen");
        EXIT_FAILURE;
    }

    while (1) {
        length = sizeof(cli_addr);
        if ((socket_fd = accept(listen_fd, (struct sockaddr *) &cli_addr, &length)) < 0)
            printf("system call accept");
        if ((pid = fork()) < 0) {
            printf("system call fork");
        }
        else {
            if (pid == 0) {    /* child */
                return http_echo(listen_fd, socket_fd);
            } else {    /* parent */
                close(socket_fd);
            }
        }
    }
<<<<<<< HEAD:http-echo/http-echo.c
}

int http_echo(int listen_fd, int socket_fd) {
    close(listen_fd);
    static char buffer[BUFFER_SIZE + 1]; /* static so zero filled */
    read(socket_fd, buffer, BUFFER_SIZE);    /* read Web request in one go */
    write(socket_fd, buffer, strlen(buffer));
    sleep(1);
    close(socket_fd);
    exit(1);
=======
>>>>>>> b54260d160c6b355b06bcc825a3e8c490737e668:http-echo/http-echo.c
}

#pragma clang diagnostic pop