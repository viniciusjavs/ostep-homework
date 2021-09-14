#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(EXIT_FAILURE);
  } else if (rc == 0) {
    printf("hello\n");
  } else {
    int rc_wait = waitpid(-1, NULL, 0);
    if (wc >= 0) {
      printf("goodbye\n");
    }
  }
}
