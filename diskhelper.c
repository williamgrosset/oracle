#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "diskhelper.h"

void* map_memory(int fd) {
  struct stat buffer;
  void* address = mmap(NULL, buffer.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (address == MAP_FAILED) {
    printf("Failed to map disk image.\n");
    close(fd);
    exit(EXIT_FAILURE);
  }
  return address;
}
