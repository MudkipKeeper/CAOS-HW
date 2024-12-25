#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 4) {
    exit(1);
  }

  int input_fd = open(argv[1], O_RDONLY);
  if (input_fd == -1) {
    exit(1);
  }
  int digits_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  int others_fd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (digits_fd == -1 || others_fd == -1) {
    close(input_fd);
    close(digits_fd);
    close(others_fd);
    exit(2);
  }
  int input_size = 512;
  char buffer[512];
  char buffer_digits[512];
  char buffer_others[512];
  input_size = read(input_fd, buffer, input_size);
  while (input_size > 0) {
    int digits_size = 0;
    int others_size = 0;
    for (int i = 0; i < input_size; i++) {
      if ('0' <= buffer[i] && buffer[i] <= '9') {
        buffer_digits[digits_size++] = buffer[i];
      } else {
        buffer_others[others_size++] = buffer[i];
      }
    }

    if (write(digits_fd, &buffer_digits, digits_size) == -1) {
      close(input_fd);
      close(digits_fd);
      close(others_fd);
      exit(3);
    }
    if (write(others_fd, &buffer_others, others_size) == -1) {
      close(input_fd);
      close(digits_fd);
      close(others_fd);
      exit(3);
    }
    input_size = read(input_fd, buffer, input_size);
  }

  if (input_size == -1) {
    close(input_fd);
    close(digits_fd);
    close(others_fd);
    exit(3);
  }
  if (close(input_fd) == -1 || close(digits_fd) == -1 ||
      close(others_fd) == -1) {
    exit(3);
  }
  close(input_fd);
  close(digits_fd);
  close(others_fd);
  return 0;
}