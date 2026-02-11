generate_crc32c(char *buffer, size_t length) {
  size_t i;
  uint32_t crc32 = ~0L;

  for (i = 0; i < length; i++){
      CRC32C(crc32, (unsigned char)buffer[i]);
  }
  return ~crc32;
}
