#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

volatile sig_atomic_t e_flag = 0;

void abrt_handler(int sig);

int main() {
  printf("start %s\n", __func__);

  if ( signal(SIGINT, abrt_handler) == SIG_ERR ) {
    exit(1);
  }

  while (!e_flag) {}

  printf("end %s\n", __func__);

  return 0;
}

void abrt_handler(int sig) {
  e_flag = 1;
}