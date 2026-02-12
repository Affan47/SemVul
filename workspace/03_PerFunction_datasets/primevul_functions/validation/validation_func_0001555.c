static int exif_process_string_raw(char **result, char *value,
                                   size_t byte_count) {


  *result = 0;
  if (byte_count) {
    (*result) = (char*)IM_MALLOC(byte_count + 1);
    CHECK_ALLOC_R((*result), byte_count + 1, 0);
    memcpy(*result, value, byte_count);
    (*result)[byte_count] = '\0';
    return byte_count+1;
  }
  return 0;
}
