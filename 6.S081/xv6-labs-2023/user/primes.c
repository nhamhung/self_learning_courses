#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

__attribute__((noreturn)) void recursive_primes(int p[2])
{
  int received_prime;
  int next;
  close(p[1]); // very important, signals to child process that parent writing to pipe has been done and child can proceed without blocking indefinitely

  if (read(p[0], &received_prime, sizeof(int)) != sizeof(int))
  {
    fprintf(2, "Read error");
    exit(1);
  }

  printf("prime %d\n", received_prime);

  if (read(p[0], &next, sizeof(int)) != 0) // if pipe still has data to be read
  {
    int new_p[2];
    pipe(new_p);

    if (fork() == 0)
    {
      recursive_primes(new_p);
    }
    else
    {
      close(new_p[0]);
      if (next % received_prime != 0)
      {
        if (write(new_p[1], &next, sizeof(int)) != sizeof(int))
        {
          fprintf(2, "Write error for %d\n", next);
          exit(1);
        }
      }

      while (read(p[0], &next, sizeof(int)) == sizeof(int))
      {
        if (next % received_prime != 0)
        {
          if (write(new_p[1], &next, sizeof(int)) != sizeof(int))
          {
            fprintf(2, "Write error for %d\n", next);
            exit(1);
          }
        }
      }

      close(p[0]);
      close(new_p[1]);
      wait(0);
    }
  }

  exit(0);
}

int main(int argc, char *argv[])
{
  // pipe for generating process
  int p[2];
  pipe(p);

  if (fork() == 0)
  {
    recursive_primes(p);
  }
  else
  {
    close(p[0]);
    for (int i = 2; i <= 35; i++)
    {
      if (write(p[1], &i, sizeof(int)) != sizeof(int))
      {
        fprintf(2, "Write error for %d\n", i);
        exit(1);
      };
    }
    close(p[1]); // close write side when done
    wait(0);     // wait for all processes to complete
    exit(0);
  }

  return 0;
}