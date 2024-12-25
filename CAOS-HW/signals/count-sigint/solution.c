#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t counter = 0;

void handle_sigint(int signo) { counter++; }

void handle_sigterm(int signo) {
  printf("%d\n", counter);
  fflush(stdout);
  exit(0);
}

int main() {
  printf("%d\n", getpid());
  fflush(stdout);

  struct sigaction sa_int, sa_term;

  sa_int.sa_handler = handle_sigint;
  sa_int.sa_flags = SA_RESTART;
  sigemptyset(&sa_int.sa_mask);
  sigaction(SIGINT, &sa_int, NULL);

  sa_term.sa_handler = handle_sigterm;
  sa_term.sa_flags = 0;
  sigemptyset(&sa_term.sa_mask);
  sigaction(SIGTERM, &sa_term, NULL);

  while (1) {
    pause();
  }

  return 0;
}
