struct __attribute__((__packed__)) superblock_t {
  uint8_t fs_id [8];
  uint16_t block_size;
  uint32_t file_system_block_count;
  uint32_t fat_start_block;
  uint32_t fat_block_count;
  uint32_t root_dir_start_block;
  uint32_t root_dir_block_count;
};

unsigned char* disk_buffer(char* file);
int get_super_block_info(unsigned char* buffer, int start, int end);
