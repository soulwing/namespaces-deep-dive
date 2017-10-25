#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(argc, argv)
int argc;
char *argv[];
{
  int child_pid, child_status;

  if (argc < 2) return 1;

  child_pid = fork();
  if (child_pid == 0) {
    execv(argv[1], argv + 1);
  }

  printf("child PID is %d\n", child_pid);
  wait(&child_status);
  printf("child exit code is %d\n", child_status>>8);
  return 0;
}
