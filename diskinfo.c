#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "diskhelper.h"

int get_fat_free_block_count() { return 0; }
int get_fat_reserv_block_count() { return 0; }
int get_fat_alloc_block_count() { return 0; }

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Enter the correct amount of args: diskinfo <file system img>\n");
    return(EXIT_FAILURE);
  }

  struct stat buffer;
  int fd = open(argv[1], O_RDWR);
  char* address = mmap(NULL, buffer.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  struct superblock_t *superblock = address;
  uint16_t block_size = htons(superblock->block_size);
  uint32_t block_count = htonl(superblock->file_system_block_count);
  uint32_t fat_start = htonl(superblock->fat_start_block);

  int free_block = 0;
  int reserv_block = 0;
  int alloc_block = 0;
  int i;
  // TODO: audit calc -> block_count (6400) * 4 + block_size (512)
  for (i = 0; i < (block_count * 4 + block_size); i += 4) {
    int block = 0;
    memcpy(&block, address + ((fat_start - 1) * block_size + i), 4);
    if (htonl(block) == 0) free_block++;
    if (htonl(block) == 1) reserv_block++;
  }
  printf("Free block:\n");
  printf("%i\n", free_block);
  printf("Reserve block:\n");
  printf("%i\n", reserv_block);
  printf("Alloc block:\n");
  printf("%i\n", block_count - (free_block + reserv_block));

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
