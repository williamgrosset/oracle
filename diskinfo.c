#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "diskhelper.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Enter the correct amount of args: diskinfo <file system img>\n");
    return(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_RDWR);
  struct stat buffer;

  char* address = mmap(NULL, buffer.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  struct superblock_t *superblock = address;
  printf("getting block size after htons: %d\n", htons(superblock->block_size));

  printf("Super block information:\n");
  printf("Block size: %d\n", htons(superblock->block_size));
  printf("Block count: %d\n", htonl(superblock->file_system_block_count));
  printf("FAT starts: %d\n", htonl(superblock->fat_start_block));
  printf("FAT blocks: %d\n", htonl(superblock->fat_block_count));
  printf("Root directory start: %d\n", htonl(superblock->root_dir_start_block));
  printf("Root directory blocks: %d\n\n", htonl(superblock->root_dir_block_count));

  printf("FAT information:\n");
  printf("Free Blocks:\n");
  printf("Reserved Blocks:\n");
  printf("Allocated Blocks:\n");

  return(EXIT_SUCCESS);
}
