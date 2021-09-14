#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int x = 100;
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(EXIT_FAILURE);
  } else {
    printf("[%d] x = %d\n", (int)getpid(), x);
    ++x; // no race condition
    printf("[%d] x = %d\n", (int)getpid(), x);
  }
}
