long syscall(long number, ...);

void _start() {
  char buffer[15] = "Hello, World!\n";
  syscall(1, 1, buffer, 14);
  syscall(60, 0);
}