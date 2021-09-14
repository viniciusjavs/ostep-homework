#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(EXIT_FAILURE);
  } else if (rc == 0) {
    printf("hello\n");
  } else {
    // delay the execution
    for (int i = 0; i < 100000; ++i)
      ;
    printf("goodbye\n");
  }
}
