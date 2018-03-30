#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "diskhelper.h"

struct dir_entry_t* get_file_entry() {
  struct dir_entry_t* file_entry;
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

  // find matching file and grab pointer to file size

  int fd2 = open(argv[2], O_RDWR | O_CREAT, 0666);
  if (fd2 < 0) {
    printf("Failed to open disk image.\n");
    close(fd2);
    return(EXIT_FAILURE);
  }

  struct dir_entry_t* file_entry = get_file_entry();
  if (htonl(file_entry->size) > 0) {

  } else {
    printf("File not found.\n");
  }

  munmap(address, buffer.st_size);
  close(fd);
  return(EXIT_SUCCESS);
}
