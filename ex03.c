#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

int child_fn(void *arg)
{
  char **argv = arg;
  execv(argv[0], argv);
}

int main(int argc, char *argv[])
{
  int child_pid, child_status;
  char stack[1024*1024];
  void *stack_top = stack + sizeof(stack);
 
  if (argc < 2) return 1;

  child_pid = clone(child_fn, stack_top, SIGCHLD, argv + 1);

  printf("child PID is %d\n", child_pid);
  waitpid(child_pid, &child_status, child_status);  /* modern wait() */
  printf("child exit code is %d\n", WEXITSTATUS(child_status));
  return 0;
}
