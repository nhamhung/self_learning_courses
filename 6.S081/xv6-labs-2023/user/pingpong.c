#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv)
{
  int parent_to_child[2];
  int child_to_parent[2];

  pipe(parent_to_child);
  pipe(child_to_parent);

  if (fork() == 0)
  {
    char child_buf[1];
    close(parent_to_child[1]);
    close(child_to_parent[0]);
    if (read(parent_to_child[0], child_buf, sizeof(child_buf)) == 1)
    {
      fprintf(1, "%d: received ping\n", getpid());
      write(child_to_parent[1], "b", 1);
    }
    exit(0);
  }
  else
  {
    char parent_buf[1];
    close(parent_to_child[0]);
    close(child_to_parent[1]);
    write(parent_to_child[1], "b", 1);
    if (read(child_to_parent[0], parent_buf, sizeof(parent_buf)))
    {
      fprintf(1, "%d: received pong\n", getpid());
    }
    exit(0);
  }
}