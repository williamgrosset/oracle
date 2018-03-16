#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void diskinfo(int argc, char* argv[]) {}
void disklist(int argc, char* argv[]) {}
void diskget(int argc, char* argv[]) {}
void diskput(int argc, char* argv[]) {}

int main(int argc, char* argv[]) {
  unsigned char *buffer;
  size_t size;
  FILE *fp;

  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    perror("Error opening file.");
    return(EXIT_FAILURE);
  }

  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  buffer = malloc(size);
  fread(buffer, sizeof *buffer, size, fp);

  int i;
  for(i = 0; i < size; i++) {
    printf("%02x ", buffer[i]); // prints a series of bytes
  }

  fclose(fp);
  free(buffer);
  return(EXIT_SUCCESS);
}
