#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "diskhelper.h"

// Super block
struct __attribute__((__packed__)) superblock_t {
  uint8_t fs_id [8];
  uint16_t block_size;
  uint32_t file_system_block_count;
  uint32_t fat_start_block;
  uint32_t fat_block_count;
  uint32_t root_dir_start_block;
  uint32_t root_dir_block_count;
};

int get_FAT_info() { return 0; }

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Enter the correct amount of args: diskinfo <file system img>\n");
    return(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_RDWR);
  struct stat buffer;
  int status = fstat(fd, &buffer);

  char* address = mmap(NULL, buffer.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  struct superblock_t *superblock = address;
  printf("getting block size after htons: %d\n", htons(superblock->block_size));

  /*
  unsigned char* buffer = disk_buffer(argv[1]);
  int block_size = get_super_block_info(buffer, 8, 10);
  int block_count = get_super_block_info(buffer, 10, 14);
  int FAT_start = get_super_block_info(buffer, 14, 18);
  int FAT_blocks = get_super_block_info(buffer, 18, 22);
  int root_dir_start = get_super_block_info(buffer, 22, 26);
  int root_dir_blocks = get_super_block_info(buffer, 26, 30);
  */

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
