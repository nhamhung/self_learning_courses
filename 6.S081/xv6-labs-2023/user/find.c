#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char *get_file_or_dir_name(char *path)
{
  // static char buf[DIRSIZ + 1];
  char *p;

  // Find first character after last slash.
  for (p = path + strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // printf("Character pointed by p: %c\n", *p);

  return p;
}

void find(char *path, char *pattern)
{
  int fd;
  struct stat st;
  struct dirent de;

  // printf("Path: %s\n", path);
  // printf("Pattern: %s\n", pattern);

  if ((fd = open(path, O_RDONLY)) < 0) // should be 3
  {
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0)
  {
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  // printf("disk device: %d, inode number: %d, type: %d, num links: %d, file size: %d\n", st.dev, st.ino, st.type, st.nlink, st.size);

  switch (st.type)
  {
  case T_DEVICE:
  case T_FILE:
    char *file_name = get_file_or_dir_name(path);

    if (strcmp(file_name, pattern) == 0)
    {
      printf("%s\n", path);
    }

    break;
  case T_DIR:
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
      if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        continue;

      char buf[512], *p;

      strcpy(buf, path);
      p = buf + strlen(buf);
      *p++ = '/';

      memmove(p, de.name, sizeof(de.name));

      find(buf, pattern);

      memset(buf, 0, sizeof(buf));
    }

    break;
  }

  close(fd); // close fd to prevent exhausting the available fd
}

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    fprintf(2, "Usage: find path pattern\n");
    exit(1);
  }

  find(argv[1], argv[2]);
  exit(0);
}