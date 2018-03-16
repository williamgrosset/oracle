#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void diskinfo(int argc, char* argv[]) {}
void disklist(int argc, char* argv[]) {}
void diskget(int argc, char* argv[]) {}
void diskput(int argc, char* argv[]) {}

int main(int argc, char* argv[]) {
  unsigned char buffer[1024];
  FILE *fp;

  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    perror("Error opening file.");
    return(EXIT_FAILURE);
  }

  fread(buffer, sizeof(buffer), 1, fp);

  int i;
  for(i = 0; i < 1024; i++) {
    printf("%x ", buffer[i]); // prints a series of bytes
  }

  fclose(fp);
  return(EXIT_SUCCESS);
}
