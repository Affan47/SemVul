static int exif_process_undefined(char **result, char *value,
                                  size_t byte_count) {


  if (byte_count) {
    PHP_STRNDUP((*result), value, byte_count);
    if (*result) return byte_count+1;
  }
  return 0;
}
