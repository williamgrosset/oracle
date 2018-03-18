#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int get_super_block_info(unsigned char* buffer, int start, int end) {
  char hex_string[1024];
  int k;
  for (k = start; k <= end; k++) {
    char temp[1024];
    snprintf(temp, sizeof(temp), "%02x", buffer[k]);
    strcat(hex_string, temp);
  }
  int number = (int)strtol(hex_string, NULL, 16);
  return number;
}

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
    // For testing purposes
    int i;
    for(i = 0; i < 12; i++) {
      printf("%x ", buffer[i]);
    }
  }

  int number = get_super_block_info(buffer, 8, 9);
  printf("block_size VALUE:\n");
  printf("%i\n", number);

  fclose(fp);
  free(buffer);
  return(EXIT_SUCCESS);
}
