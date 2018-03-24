#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "diskhelper.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Enter the correct amount of arguments: disklist <file system image> <directory>\n");
    return(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_RDWR);
  struct stat buffer;
  void* address = mmap(NULL, buffer.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  struct superblock_t *superblock = address;
  uint16_t block_size = htons(superblock->block_size);
  uint32_t root_dir_start_block = htonl(superblock->root_dir_start_block);
  int offset = (root_dir_start_block) * block_size;
  struct dir_entry_t *dir_entry = address + offset;

  int i;
  for (i = 1; i <= 3; i++) {
    printf("Status of file in root directory:\n");
    printf("%x\n", dir_entry->status);
    printf("File name:\n");
    printf("%s\n", dir_entry->filename);
    dir_entry = dir_entry + i;
  }

  return(EXIT_SUCCESS);
}
