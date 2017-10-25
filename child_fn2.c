#define _GNU_SOURCE
#include <sys/mount.h>

#include <stdio.h>
#include <unistd.h>

int child_fn(void *arg)
{
  char *default_argv[] = { "/bin/bash", "--rcfile", "~/.demorc", NULL };
  char **argv = arg;
  if (argv[0] == NULL) argv = default_argv;

  printf("my PID is %d\n", getpid());

  /* make / and /proc private mounts private to our mount namespace */
  mount(NULL, "/", NULL, MS_PRIVATE, NULL);
  mount(NULL, "/proc", NULL, MS_PRIVATE, NULL);

  /* re-mount /proc with details from our PID namespace */
  mount("proc", "/proc", "proc", 0, 0);

  execv(argv[0], argv);
  perror("execv");
  return 1;
}
