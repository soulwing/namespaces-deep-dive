#define _GNU_SOURCE

#include <sys/types.h>

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define UID_MAP_FORMAT      "/proc/%ld/uid_map"
#define GID_MAP_FORMAT      "/proc/%ld/gid_map"
#define SETGROUPS_FORMAT    "/proc/%ld/setgroups"

static int write_id_mapping(pid_t pid, uid_t from_id, uid_t to_id, 
    const char *path_format) 
{
  size_t size = strlen(path_format) + 16;
  char *path = (char *) malloc(size);
  snprintf(path, size, path_format, pid);

  char mapping[100];
  snprintf(mapping, sizeof(mapping), "%ld %ld 1\n", (long) from_id, 
      (long) to_id);    
  
  int fd = open(path, O_WRONLY | O_CREAT);
  if (fd == -1) {
    fprintf(stderr, "open: %s: %s\n", path, strerror(errno));
    return -1;
  }

  if (write(fd, mapping, strlen(mapping)) != strlen(mapping)) {
    fprintf(stderr, "write: %s: %m\n", path);
    return -1;
  }

  if (close(fd) != 0) {
    fprintf(stderr, "close: %s: %m\n", path);
    return -1;
  }
 
  free(path);
  return 0;
}

static int write_setgroups_mode(pid_t pid, char *mode)
{
  int fd;
  char setgroups_path[PATH_MAX];

  snprintf(setgroups_path, PATH_MAX, SETGROUPS_FORMAT, (long) pid);
  fd = open(setgroups_path, O_RDWR);
  if (fd == -1) {
    if (errno != ENOENT) {
      fprintf(stderr, "open: %s: %m\n", setgroups_path);
      return -1;
    }
  }

  if (write(fd, mode, strlen(mode)) == -1) {
    fprintf(stderr, "write: %s: %m\n", setgroups_path);
    return -1;
  }

  if (close(fd) == -1) {
    fprintf(stderr, "close: %s: %m\n", setgroups_path);
    return -1;
  }

  return 0;
}

int prepare_user_namespace(pid_t pid, uid_t uid, gid_t gid)
{
  if (write_setgroups_mode(pid, "deny") == -1) return -1;
  if (write_id_mapping(pid, 0, uid, UID_MAP_FORMAT) == -1) return -1;
  if (write_id_mapping(pid, 0, gid, GID_MAP_FORMAT) == -1) return -1;
  return 0;
}

