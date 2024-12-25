#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
void find_substring(const char *data, size_t size, const char *substring) {
  size_t substring_len = strlen(substring);
  if (substring == 0 || size < substring_len) {
    return;
  }
  for (size_t i = 0; i <= size - substring_len; i++) {
    if (strncmp(data + i, substring, substring_len) == 0) {
      printf("%ld ", i);
    }
  }
}
int main(int argc, char *argv[]) {
  if (argc < 3) {
    exit(1);
  }

  const char *filename = argv[1];
  const char *data = argv[2];

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

  char *buffer = (char *)mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
  close(fd);

  find_substring(buffer, file_size, data);

  munmap(buffer, file_size);
  return 0;
}
