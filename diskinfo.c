#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "diskhelper.h"

int get_fat_free_block_count(char* address, int fat_start, int block_size, int block_count) {
  // TODO: remove duplicated loop logic
  // TODO: audit calc -> block_count (6400) * 4 + block_size (512)
  int fat_free_blocks = 0;
  int i;
  for (i = 0; i < (block_count * 4 + block_size); i += 4) {
    int block = 0;
    memcpy(&block, address + ((fat_start - 1) * block_size + i), 4);
    if (htonl(block) == 0) fat_free_blocks++;
  }
  return fat_free_blocks;
}

int get_fat_reserv_block_count(char* address, int fat_start, int block_size, int block_count) {
  // TODO: audit calc -> block_count (6400) * 4 + block_size (512)
  int fat_reserv_blocks = 0;
  int i;
  for (i = 0; i < (block_count * 4 + block_size); i += 4) {
    int block = 0;
    memcpy(&block, address + ((fat_start - 1) * block_size + i), 4);
    if (htonl(block) == 1) fat_reserv_blocks++;
  }
  return fat_reserv_blocks;
}

int get_fat_alloc_block_count(int block_count, int fat_free_blocks, int fat_reserv_blocks) {
  return block_count - (fat_free_blocks + fat_reserv_blocks);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Enter the correct amount of args: diskinfo <file system img>\n");
    return(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_RDWR);
  struct stat buffer;
  char* address = mmap(NULL, buffer.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  struct superblock_t *superblock = address;
  uint16_t block_size = htons(superblock->block_size);
  uint32_t block_count = htonl(superblock->file_system_block_count);
  uint32_t fat_start = htonl(superblock->fat_start_block);
  int fat_free_blocks = get_fat_free_block_count(address, fat_start, block_size, block_count);
  int fat_reserv_blocks = get_fat_reserv_block_count(address, fat_start, block_size, block_count);
  int fat_alloc_blocks = get_fat_alloc_block_count(block_count, fat_free_blocks, fat_reserv_blocks);

  printf("Super block information:\n");
  printf("Block size: %d\n", htons(superblock->block_size));
  printf("Block count: %d\n", htonl(superblock->file_system_block_count));
  printf("FAT starts: %d\n", htonl(superblock->fat_start_block));
  printf("FAT blocks: %d\n", htonl(superblock->fat_block_count));
  printf("Root directory start: %d\n", htonl(superblock->root_dir_start_block));
  printf("Root directory blocks: %d\n\n", htonl(superblock->root_dir_block_count));
  printf("FAT information:\n");
  printf("Free Blocks: %i\n", fat_free_blocks);
  printf("Reserved Blocks: %i\n", fat_reserv_blocks);
  printf("Allocated Blocks: %i\n", fat_alloc_blocks);

  return(EXIT_SUCCESS);
}
