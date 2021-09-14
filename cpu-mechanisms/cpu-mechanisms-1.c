#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
  struct timeval tv1, tv2;

  gettimeofday(&tv1, NULL);
  for (int i = 0; i < 100000; ++i)
    ;
  gettimeofday(&tv2, NULL);

  long loop_overhead = tv2.tv_usec - tv1.tv_usec;

  gettimeofday(&tv1, NULL);
  for (int i = 0; i < 100000; ++i)
    read(STDIN_FILENO, NULL, 0); // a null system-call
  gettimeofday(&tv2, NULL);

  printf("%ld ns\n", (tv2.tv_usec - tv1.tv_usec - loop_overhead) / 100);
}
