long syscall(long number, ...);

void _start() {
  char buffer[512];
  int input_size = 0;
  int size = 500;
  while ((input_size = syscall(0, 0, buffer, size)) > 0) {
    if (syscall(1, 1, buffer, input_size) == -1) {
      syscall(60, 0);
    }
  }
  syscall(60, 0);
}