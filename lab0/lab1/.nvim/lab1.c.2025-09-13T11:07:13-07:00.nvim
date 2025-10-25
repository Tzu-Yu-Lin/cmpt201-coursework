#define _POSIX_C_SOURSE 200809L
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char *b = NULL;
  size_t bsize = 0;
  printf("enter: ");
  ssize_t r = getline(&b, &bsize, stdin);
  if (r == -1) {
    free(b);
    return 1;
  }
  printf("\nYou entered ((%zd-1) characters): %s", r, b);
  free(b);
  return 0;
}
