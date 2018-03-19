#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char* fill_buffer(char* file) {
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

void diskinfo(int argc, char* argv[]) {}
void disklist(int argc, char* argv[]) {}
void diskget(int argc, char* argv[]) {}
void diskput(int argc, char* argv[]) {}

int main(int argc, char* argv[]) {
  unsigned char* buffer = fill_buffer(argv[1]);

  /* DISKINFO */
  int block_size = get_super_block_info(buffer, 8, 10);
  int block_count = get_super_block_info(buffer, 10, 14);
  int FAT_start = get_super_block_info(buffer, 14, 18);
  int FAT_blocks = get_super_block_info(buffer, 18, 22);
  int root_dir_start = get_super_block_info(buffer, 22, 26);
  int root_dir_blocks = get_super_block_info(buffer, 26, 30);

  printf("Super block information:\n");
  printf("Block size: %i\n", block_size);
  printf("Block count: %i\n", block_count);
  printf("FAT starts: %i\n", FAT_start);
  printf("FAT blocks: %i\n", FAT_blocks);
  printf("Root directory start: %i\n", root_dir_start);
  printf("Root directory blocks: %i\n\n", root_dir_blocks);

  /* DISKLIST */

  return(EXIT_SUCCESS);
}
