#include <assert.h>
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
    execl("/bin/ls", ".", (char *)NULL);
  } else {
    int rc_wait = wait(NULL);
    assert(wc >= 0);
  }
}
