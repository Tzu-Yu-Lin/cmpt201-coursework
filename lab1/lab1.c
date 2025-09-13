#define _GNU_SOURSE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
  char *b = NULL;
  size_t bsize = 0;
  printf("enter: ");
  ssize_t num = getline(&b, &bsize, stdin);
  if (num == -1) {
    free(b);
    return 1;
  }

  if (num > 0 && b[num - 1] == '\n') {
    b[num - 1] = '\0';
  }

  char *save = NULL;
  char *tok = strtok_r(b, " ", &save);
  while (tok != NULL) {
    printf("%s\n", tok);
    tok = strtok_r(NULL, " ", &save);
  }
  free(b);
  return 0;
}
