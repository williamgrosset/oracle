#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

  if (fread(buffer, sizeof *buffer, size, fp) != size) {
    printf("Error while reading file.");
    return(EXIT_FAILURE);
  } else {
    int i;
    for(i = 0; i < 12; i++) {
      printf("%x ", buffer[i]);
    }
  }

  printf("Block size:\n");
  char block_size[size];
  int k;
  for (k = 8; k < 10; k++) {
    char temp[1024];
    snprintf(temp, sizeof(temp), "%02x", buffer[k]);
    strcat(block_size, temp);
  }
  printf("block_size ARRAY:\n");
  printf("%s\n", block_size);

  fclose(fp);
  free(buffer);
  return(EXIT_SUCCESS);
}
