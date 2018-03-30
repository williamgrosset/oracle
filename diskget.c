#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "diskhelper.h"

struct dir_entry_t* get_file_entry(char* filename, struct dir_entry_t* dir_entry, uint32_t dir_block_count) {
  struct dir_entry_t* file_entry = dir_entry;
  int i = 1;
  while (i <= dir_block_count) {
    if (dir_entry->status == 0) break;
    if (filename == dir_entry->filename) {
      file_entry = dir_entry;
      return file_entry;
    }
    dir_entry += i++;
  }
  return file_entry;
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    printf("Enter the correct amount of arguments: diskget <file system image> <file> <file>.\n");
    return(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    printf("Failed to open disk image.\n");
    close(fd);
    return(EXIT_FAILURE);
  }

  struct stat buffer;
  void* address = mmap(NULL, buffer.st_size, PROT_READ, MAP_SHARED, fd, 0);
  struct superblock_t* superblock = address;
  uint16_t block_size = htons(superblock->block_size);
  uint32_t root_dir_start_block = htonl(superblock->root_dir_start_block);
  uint32_t root_dir_block_count = htonl(superblock->root_dir_block_count);
  int offset = (root_dir_start_block) * block_size;
  struct dir_entry_t* root_dir_entry = address + offset;
  struct dir_entry_t* file_entry = get_file_entry(argv[1], root_dir_entry, root_dir_block_count);

  // find matching file and grab pointer to file size
  if (htonl(file_entry->size) > 0) {
    printf("ay\n");
  } else {
    printf("File not found.\n");
  }

  /*
  int fd2 = open(argv[2], O_RDWR | O_CREAT, 0666);
  if (fd2 < 0) {
    printf("Failed to open disk image.\n");
    close(fd2);
    return(EXIT_FAILURE);
  }*/

  munmap(address, buffer.st_size);
  close(fd);
  return(EXIT_SUCCESS);
}
