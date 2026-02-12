static int exif_process_string(char **result, char *value,
                               size_t byte_count) {


    if ((byte_count=php_strnlen(value, byte_count)) > 0) {
      return exif_process_undefined(result, value, byte_count);
    }
    PHP_STRNDUP((*result), "", 1);
    if (*result) return byte_count+1;
    return 0;
}
