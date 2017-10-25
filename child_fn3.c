#define _GNU_SOURCE
#include <sys/mount.h>

#include <stdio.h>
#include <unistd.h>

#include "child_fn3.h"

int prepare_mount_namespace(void);

int child_fn(void *arg, int pipe_fds[])
{
  struct child_args *args = arg;

  char *default_argv[] = { "/bin/bash", "--rcfile", "~/.demorc", NULL };
  char **argv = args->argv;
  if (args->argv[0] == NULL) argv = default_argv;

  printf("my PID is %d\n", getpid());

  /* wait for parent to tell us to proceed */
  close(args->pipe_fds[1]);  /* close the writing end of the pipe */
  char buf[3];
  int num_read = read(args->pipe_fds[0], buf, sizeof(buf));
  if (num_read < 0) return 1;

  if (prepare_mount_namespace() == -1) return 1;

  execv(argv[0], argv);
  perror("execv");
  return 1;
}
