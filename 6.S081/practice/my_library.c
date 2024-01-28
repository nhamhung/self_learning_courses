#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void try_fork(void)
{
  int pid = fork();

  if (pid == 0)
  {
    printf("Child: %d is executing\n", getpid());
    exit(0);
  }
  else if (pid > 0)
  {
    printf("Parent: %d, child: %d\n", getpid(), pid);
    // wait for child process to complete
    wait(0);
    printf("Child %d has finished", pid);
  }
  else
  {
    printf("Fork error\n");
  }
}

void try_exec(void)
{
  // declare an array of pointers to characters because each argument is a variable-length string
  char *argv[3];
  argv[0] = "echo";
  argv[1] = "Hi";
  argv[2] = 0;

  execv("/bin/echo", argv);

  // should not be run if exec succeeds as it replaces current program with program stored in /bin/echo with argument list "echo Hi"
  printf("exec error\n");
}

void try_file_descriptor()
{
  char buf[512];
}