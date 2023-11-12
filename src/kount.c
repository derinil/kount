#include "kount.h"
#include <arm_neon.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

uint8x16_t create8x16(uint8_t x) {
  uint8_t v[16] = {0};
  for (int i = 0; i < 16; i++) {
    v[i] = x;
  }

  return vld1q_u8(v);
}

int main(int argc, char *argv[]) {
  if (argc == 1)
    return 4;
  char *file_name = argv[argc - 1];
  int fd = open(file_name, O_RDONLY);
  if (fd < 0)
    return 1;
  struct stat fs;
  int err = fstat(fd, &fs);
  if (err < 0)
    return 2;
  size_t len = fs.st_size;

  int flags = MAP_PRIVATE;
  uint8_t *map = mmap(NULL, fs.st_size, PROT_READ, flags, fd, 0);
  if (!map)
    return 3;

  size_t count = 0;

  const uint8_t needle = argc == 3 ? argv[2][0] : '\n';

#define STRIDE 16

  if (len < STRIDE) {
    for (size_t i = 0; i < len; i++) {
      count += map[i] == needle;
    }
    goto end;
  }

  uint8x16_t needle_mask = create8x16(needle);
// 0 for AND, 1 for SHIFT
#define METHOD 1
#if METHOD == 0
  uint8x16_t last_set_bit = create8x16(1);
#endif
  size_t off = 0;
  uint8x16_t buf = {0};

  size_t max = len % STRIDE == 0 ? len : len - STRIDE;

  while (off < max) {
    buf = vld1q_u8(map + off);
#if METHOD == 0
    count += vaddvq_u8(vandq_u8(last_set_bit, vceqq_u8(buf, needle_mask)));
#else
    count += vaddvq_u8(vshrq_n_u8(vceqq_u8(buf, needle_mask), 7));
#endif
    off += STRIDE;
  }

  for (size_t i = off; i < len; i++) {
    count += map[i] == needle;
  }

end:
  printf("%lu\n", count);
  munmap(map, fs.st_size);
  close(fd);
  return 0;
}
