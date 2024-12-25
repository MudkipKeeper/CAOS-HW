#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
  char filename[255];
  struct stat file_stat;
  int total_size = 0;

  while (fgets(filename, 255, stdin) != NULL) {
    filename[strcspn(filename, "\n")] = '\0';
    if (stat(filename, &file_stat) == -1) {
      continue;
    }
    if (S_ISREG(file_stat.st_mode)) {
      total_size += file_stat.st_size;
    }
  }
  printf("%d\n", total_size);
  return 0;
}
