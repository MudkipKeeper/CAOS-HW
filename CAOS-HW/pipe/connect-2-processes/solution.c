#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    exit(EXIT_FAILURE);
  }

  int pipefd[2];
  pid_t pid1, pid2;

  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  if ((pid1 = fork()) == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid1 == 0) {
    close(pipefd[0]);
    dup2(pipefd[1], 1);
    close(pipefd[1]);
    execlp(argv[1], argv[1], (char *)NULL);
    perror("execlp");
    exit(EXIT_FAILURE);
  }

  pid2 = fork();
  if (pid2 == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid2 == 0) {
    close(pipefd[1]);
    dup2(pipefd[0], 0);
    close(pipefd[0]);
    execlp(argv[2], argv[2], (char *)NULL);
    perror("execlp");
    exit(EXIT_FAILURE);
  }
  close(pipefd[0]);
  close(pipefd[1]);
  return 0;
}
