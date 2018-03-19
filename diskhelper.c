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
    for(i = 0; i < 20; i++) {
      printf("%02x ", buffer[i]);
    }
  }

  fclose(fp);
  // free(buffer) ?
  return buffer;
}

int get_super_block_info(unsigned char* buffer, int start, int end) {
  char hex_val[1024];
  int i;
  for (i = start; i < end; i++) {
    char hex_sub[1024];
    snprintf(hex_sub, sizeof(hex_sub), "%02x", buffer[i]);
    strcat(hex_val, hex_sub);
    memset(hex_sub, 0, sizeof(hex_sub));
  }

  int number = (int)strtol(hex_val, NULL, 16);
  memset(hex_val, 0, sizeof(hex_val));
  return number;
}
