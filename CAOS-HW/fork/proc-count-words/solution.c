#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char const* argv[]) {
  const int page_size = 4096;
  char buffer[page_size];
  int count_words = 0;
  int child_value = 0;
  while (1) {
    pid_t process_id;
    if (-1 == (process_id = fork())) {
      break;
    } else if (0 == process_id) {
      int res = (scanf("%s", buffer) == 1 ? 0 : 1);
      return res;
    } else {
      wait(&child_value);
      if (child_value != 0) {
        break;
      } else {
        count_words++;
      }
    }
  }
  printf("%d\n", count_words);
}