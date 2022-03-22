#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// int computeSum(int argc, char **argv) {
//
// }

int main(int argc, char *argv[]) {
  pid_t C1, C2, pid;
  int wait1, wait2, childStatus1, childStatus2, exitc1, exitc2;
  int sum = 0;
  int product = 1;

  if (fork()) {
    // C1 = fork();
    wait1 = wait(&childStatus1);
    exitc1 = WEXITSTATUS(childStatus1);

    // if (C1 < 0) {
    //   printf("Error: fork 1 failed\n");
    //   return -2;
    // }
  } else {
    // if (C1 == 0) {
    pid = getpid();
    printf("[C1] (pid:%d): ", pid);

    for (int i = 0; i < argc; i++) {
      sum = sum + atoi(argv[i]);
    }
    if (sum < 0) {
      printf("The sum of user inputs is %d\n", sum);
      exit(1);
    } else {
      printf("The sum of user inputs is %d\n", sum);
      exit(0);
    }
    //}
  }

  if (fork()) {
    // else {
    // C2 = fork();
    wait2 = wait(&childStatus2);
    exitc2 = WEXITSTATUS(childStatus2);
  }
  // if (C2 < 0) {
  //   printf("Error: fork 1 failed\n");
  // }
  // return -2;

  else {
    // if (C2 == 0) {
    pid = getpid();
    printf("[C2] (pid:%d): ", pid);

    for (int i = 1; i < argc; i++) {
      product = product * atoi(argv[i]);
    }
    if (product < 0) {
      printf("The product of user inputs is %d\n", product);
      exit(1);
    } else {
      printf("The product of user inputs is %d\n", product);
      exit(0);
    }
    //}
  }
  // else {
  // wait1 = wait(&childStatus1);
  // exitc1 = WEXITSTATUS(childStatus1);
  // wait2 = wait(&childStatus2);
  // exitc2 = WEXITSTATUS(childStatus2);

  pid = getpid();
  if (exitc1 == 1) {
    printf("[P] (pid:%d): sum was negative\n", pid);
  } else {
    printf("[P] (pid:%d): sum was nonnegative\n", pid);
  }

  if (exitc2 == 1) {
    printf("[P] (pid:%d): product was negative\n", pid);
  } else {
    printf("[P] (pid:%d): product was nonnegative\n", pid);
  }
  exit(0);
  //}

  //}
}
