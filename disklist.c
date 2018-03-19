#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diskhelper.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Enter the correct amount of args: disklist <file system img> <directory>\n");
    return(EXIT_FAILURE);
  }

  unsigned char* buffer = disk_buffer(argv[1]);
  int root_dir_start = get_super_block_info(buffer, 22, 26);
  int root_dir_blocks = get_super_block_info(buffer, 26, 30);
  
  printf("\n%x\n", buffer[27136]);

  //printf("Super block information:\n");
  //printf("Root directory start: %i\n", root_dir_start);
  //printf("Root directory blocks: %i\n\n", root_dir_blocks);

  return(EXIT_SUCCESS);
}
