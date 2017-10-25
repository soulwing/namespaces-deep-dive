#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "child_fn3.h"

int child_fn(void *);
int prepare_user_namespace(pid_t, uid_t, gid_t);

int main(int argc, char *argv[])
{
  int child_pid, child_status;
  char stack[1024*1024];
  void *stack_top = stack + sizeof(stack);
 
  struct child_args child_args;
  child_args.argv = argv + 1;

  /* use a pipe to inform child when we're ready */
  pipe(child_args.pipe_fds);   

  int ns_flags = CLONE_NEWPID | CLONE_NEWNS | CLONE_NEWUSER | CLONE_NEWUTS;
  child_pid = clone(child_fn, stack_top, ns_flags | SIGCHLD, &child_args);
  if (child_pid == -1) {
    perror("clone");
    return 1;
  }

  printf("child PID is %d\n", child_pid);

  if (prepare_user_namespace(child_pid, getuid(), getgid()) == -1) return 1;

  /* notify child that it may proceed */
  close(child_args.pipe_fds[0]);   /* close the reading end of the pipe */
  write(child_args.pipe_fds[1], "OK", strlen("OK"));
  close(child_args.pipe_fds[1]);

  waitpid(child_pid, &child_status, child_status);
  printf("child exit code is %d\n", WEXITSTATUS(child_status));
  return 0;
}
