#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void recursive_print(int iter, int N);

int main(int argc, char const* argv[]) {
  int N;
  // printf("fksdmksmd");
  sscanf(argv[1], "%d", &N);
  recursive_print(N, N);
  return 0;
}

void recursive_print(int x, int N) {
  if (x <= 0) return;
  pid_t process_id;
  if (-1 == (process_id = fork())) {
    perror("fork");
  } else if (0 == process_id) {
    recursive_print(x - 1, N);
    exit(0);
  } else {
    int res;
    wait(&res);
    if (res != 0) {
      perror("fork");
    }
    printf("%d", x);
    if (x == N) {
      printf("\n");
    } else {
      printf(" ");
    }
  }
}
