
#define _GNU_SOURCE
#include <sys/mount.h>
#include <stdio.h>

int prepare_mount_namespace(void)
{
  if (mount(NULL, "/", NULL, MS_PRIVATE, 0) == -1) {
    perror("remount /:");
    return -1;  
  }
  if (mount(NULL, "/proc", NULL, MS_PRIVATE, 0) == -1) {
    perror("remount /:");
    return -1;  
  }
  if (mount("proc", "/proc", "proc", 0, 0) == -1) {
    perror("remount /:");
    return -1;  
  }

  return 0;
}
