#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "diskhelper.h"

/*
* TODO:
*  + Handle finding directory from input
*  + Support for sub-directories
*/

char get_file_type(uint8_t type) {
  if (type == 5) {
    return 'D';
  }
  else {
    return 'F';
  }
}

void print_root_dir_content(struct dir_entry_t* dir_entry, uint32_t dir_block_count) {
  int i = 1;
  while (i <= dir_block_count) {
    if (dir_entry->status == 0) break;
    struct dir_entry_timedate_t modify_time_struct = dir_entry->modify_time;
    printf("%c %10d %30s %04d/%02d/%02d %02d:%02d:%02d\n",
            get_file_type(dir_entry->status), htonl(dir_entry->size), dir_entry->filename,
            htons(modify_time_struct.year), modify_time_struct.month, modify_time_struct.day,
            modify_time_struct.hour, modify_time_struct.minute, modify_time_struct.second);
    dir_entry += i++;
  }
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Enter the correct amount of arguments: disklist <file system image> <directory>\n");
    return(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_RDWR);
  struct stat buffer;
  void* address = mmap(NULL, buffer.st_size, PROT_READ, MAP_SHARED, fd, 0);
  struct superblock_t *superblock = address;
  uint16_t block_size = htons(superblock->block_size);
  uint32_t root_dir_start_block = htonl(superblock->root_dir_start_block);
  uint32_t root_dir_block_count = htonl(superblock->root_dir_block_count);
  int offset = (root_dir_start_block) * block_size;
  struct dir_entry_t *dir_entry = address + offset;

  print_root_dir_content(dir_entry, root_dir_block_count);

  return(EXIT_SUCCESS);
}
