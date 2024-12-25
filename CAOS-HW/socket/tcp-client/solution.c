#include <arpa/inet.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error_exit(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

void close_socket(int sockfd) {
  shutdown(sockfd, SHUT_RDWR);
  close(sockfd);
}

bool abort_connection(int status) {
  if (status == 0) return true;
  if (status == -1 && errno == ECONNRESET) return true;
  return false;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    error_exit("Invalid argument count");
  }

  uint16_t port = 0;
  sscanf(argv[2], "%hd", &port);

  struct sockaddr_in addr;
  addr.sin_port = htons(port);
  addr.sin_family = AF_INET;

  if (inet_pton(AF_INET, argv[1], &addr.sin_addr) <= 0) {
    error_exit("Invalid IP address format");
  }

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    error_exit("Socket creation failed");
  }

  if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    close(sockfd);
    error_exit("Connection failed");
  }
  int number = 0;
  while (scanf("%d", &number) != EOF) {
    int sended = send(sockfd, &number, sizeof(number), 0);
    if (abort_connection(sended)) {
      close_socket(sockfd);
      return 0;
    }
    if (sended == -1) {
      close_socket(sockfd);
      error_exit("Failed to send data");
    }
    int received = recv(sockfd, &number, sizeof(number), 0);
    if (abort_connection(received)) {
      close_socket(sockfd);
      return 0;
    }
    if (received == -1) {
      close_socket(sockfd);
      error_exit("Failed to receive data");
    }
    printf("%d ", number);
  }
  close_socket(sockfd);
  return 0;
}
