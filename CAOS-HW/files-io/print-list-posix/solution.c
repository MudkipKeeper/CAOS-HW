#define _XOPEN_SOURCE 500

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct Item {
  int value;
  uint32_t next_pointer;
};

int main(int argc, char *argv[]) {
  int fd = open(argv[1], O_RDONLY);
  struct Item buffer;
  int input_size = 512;
  for (uint32_t offset = 0;; offset = buffer.next_pointer) {
    input_size = pread(fd, &buffer, sizeof(struct Item), offset);
    if (input_size == 0) break;
    printf("%d ", buffer.value);
    if (buffer.next_pointer == 0) break;
  }
  close(fd);
  return 0;
}