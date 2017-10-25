#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

int child_fn(void *arg);

int main(int argc, char *argv[])
{
  int child_pid, child_status;
  char stack[1024*1024];
  void *stack_top = stack + sizeof(stack);
 
  int ns_flags = CLONE_NEWPID | CLONE_NEWNS | CLONE_NEWUSER;
  child_pid = clone(child_fn, stack_top, ns_flags | SIGCHLD, argv + 1);
  if (child_pid == -1) {
    perror("clone");
    return 1;
  }

  printf("child PID is %d\n", child_pid);
  waitpid(child_pid, &child_status, child_status);
  printf("child exit code is %d\n", WEXITSTATUS(child_status));
  return 0;
}
