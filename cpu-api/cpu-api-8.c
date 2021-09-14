#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pipefd[2];
  char buf;

  if (pipe(pipefd) < 0) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid_t p1 = fork();

  if (p1 < 0) {
    perror("fork child 1");
    exit(EXIT_FAILURE);
  } else if (p1 == 0) {
    close(pipefd[0]); // close unused read end
    /* write STDIN to pipe */
    while (read(STDIN_FILENO, &buf, 1) > 0)
      write(pipefd[1], &buf, 1);
    close(pipefd[1]); // reader will see EOF
  } else {
    pid_t p2 = fork();
    if (p2 < 0) {
      perror("fork child 2");
      exit(EXIT_FAILURE);
    } else if (p2 == 0) {
      close(pipefd[1]); // Close unused write end
      /* read from pipe and writes to STDOUT */
      while (read(pipefd[0], &buf, 1) > 0)
        write(STDOUT_FILENO, &buf, 1);
      close(pipefd[0]);
    } else {
      wait(NULL); // wait for a child
    }
  }
}
