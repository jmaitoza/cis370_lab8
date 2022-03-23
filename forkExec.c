#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFSIZE 512

int ForkExec(char *temp[]) {
  pid_t pid;
  pid = fork();
  if (pid == 0) {
    execvp(temp[0], temp);
    exit(0);
  }

  return 0;
}

int main(int argc, char *argv[]) {
  ForkExec(argv + 1);
  write(1, "Done\n", 5);
  return 1;
}
