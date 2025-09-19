#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  char *line = NULL;
  size_t n;

  for (;;) {
    printf("Please enter a command:\n");
    ssize_t len = getline(&line, &n, stdin);

    if (len == -1) {
      perror("Failed to read line!\n");
      break;
    }

    if (line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }

    if (len == 1) {
      continue;
    }

    pid_t pid = fork();
    if (pid == -1) {
      perror("Failed to fork!\n");
      break;
    } else if (pid == 0) {
      if (execlp(line, line, (char *)NULL) == -1) {
        perror("Exec failure");
        exit(1);
      }
    } else {
      int status;
      waitpid(pid, &status, 0);
    }
  }

  free(line);
  return 0;
}
