#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pipefd1[2], pipefd2[2];

  cpu_set_t set;

  struct timeval tv1, tv2;

  if (pipe(pipefd1) < 0 || pipe(pipefd2) < 0) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  char buf = 0;
  write(pipefd1[1], &buf, 1);

  CPU_ZERO(&set);

  pid_t rc = fork();

  if (rc < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (rc == 0) {
    CPU_SET(0, &set);

    read(pipefd1[0], &buf, 1);
    write(pipefd2[1], &buf, 1);
    read(pipefd1[0], &buf, 1); // context switch occurs
  } else {
    CPU_SET(0, &set);

    gettimeofday(&tv1, NULL);
    read(pipefd2[0], &buf, 1); // context switch occurs
    gettimeofday(&tv2, NULL);
    write(pipefd1[1], &buf, 1);
    wait(NULL);
    printf("%ld\n", (tv2.tv_usec - tv1.tv_usec) / 2);
  }
}
