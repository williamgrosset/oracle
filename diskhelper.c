#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diskhelper.h"

unsigned char* disk_buffer(char* file) {
  unsigned char* buffer;
  size_t size;
  FILE *fp;

  fp = fopen(file, "r");
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
    for(i = 0; i < 0; i++) {
      printf("%02x ", buffer[i]);
    }
  }

  fclose(fp);
  // free(buffer) ?
  return buffer;
}
