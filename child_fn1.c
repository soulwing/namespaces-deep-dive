#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

int child_fn(void *arg)
{
  char *default_argv[] = { "/bin/bash", "--rcfile", "~/.demorc", NULL };

  char **argv = arg;

  if (argv[0] == NULL) argv = default_argv;

  printf("my PID is %d\n", getpid());   /* should print 'my PID is 1' */

  execv(argv[0], argv);
  perror("execv");
  return 1;
}
