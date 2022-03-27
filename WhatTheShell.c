// Joshua Maitoza
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 128 // max length of user command

int ForkExec(char *temp[]) {
  pid_t pid;
  int childStatus, waitC;
  pid = fork();
  waitC = wait(&childStatus);
  if (pid == 0) {
    execvp(temp[0], temp);
    exit(0);
  }
  int exitC = WEXITSTATUS(childStatus);
  return 0;
}

int main(void) {
  int count = 0;
  while (1) {
    printf("WhatTheShell> "); // Name of shell
    fflush(stdout);

    /*
      After reading user input, the steps are:
      (1) create an array of character strings (args)
      (2) fork a child process using fork()
      (3) the child process will invoke execvp()
      (4) parent will invoke wait()
    */
    char line[MAX_LINE] = "\0";
    char *args[10] = {"\0", "\0", "\0", "\0", "\0",
                      "\0", "\0", "\0", "\0", "\0"};
    const char space[10] = " ";
    char *copy[MAX_LINE];
    char *token;
    // fgets(line, MAX_LINE, stdout);
    read(0, line, MAX_LINE);

    int line_len = strlen(line);
    line[line_len - 1] = 0; // strip line of last character

    token = strtok(line, space); // gets first token

    // step through the other tokens
    while (token != NULL) {
      args[count] = token;

      // printf(" %s\n", args[count]); // debug print
      token = strtok(NULL, space);
      count++; // incrememnt array counter to next token
    }

    ForkExec(args);
    count = 0;
  }
  return 0;
}
