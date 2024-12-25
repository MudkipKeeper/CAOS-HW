#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

struct Item {
  int value;
  uint32_t next_pointer;
};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    exit(1);
  }

  const char *filename = argv[1];
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    exit(1);
  }

  struct stat st;
  if (fstat(fd, &st) == -1) {
    close(fd);
    exit(1);
  }
  size_t file_size = st.st_size;
  if (file_size == 0) {
    close(fd);
    exit(0);
  }
  int *buffer = (int *)mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);

  close(fd);
  for (size_t cur = 0; cur < file_size;) {
    struct Item *item = (struct Item *)((char *)buffer + cur);
    printf("%d ", item->value);
    if (item->next_pointer == 0) {
      break;
    }
    cur = item->next_pointer;
  }
  munmap(buffer, file_size);
  return 0;
}
