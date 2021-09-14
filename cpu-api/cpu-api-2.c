#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int fd = open("./cpu-api-2.out", O_CREAT | O_RDWR, S_IRUSR);
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed");
    exit(EXIT_FAILURE);
  } else {
    // non-deterministic output
    for (int i = 0; i < 10; ++i)
      dprintf(fd, "[%d] %d\n", (int)getpid(), i);
  }
}
