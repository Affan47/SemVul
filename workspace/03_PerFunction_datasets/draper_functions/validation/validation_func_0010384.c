ExUtilReadFromStdin(const uint8_t** data, size_t* data_size) {
  static const size_t kBlockSize = 16384;
  size_t max_size = 0;
  size_t size = 0;
  uint8_t* input = NULL;

  if (data == NULL || data_size == NULL) return 0;
  *data = NULL;
  *data_size = 0;

  if (!ExUtilSetBinaryMode(stdin)) return 0;

  while (!feof(stdin)) {

    const size_t extra_size = (max_size == 0) ? kBlockSize : max_size;
    void* const new_data = realloc(input, max_size + extra_size);
    if (new_data == NULL) goto Error;
    input = (uint8_t*)new_data;
    max_size += extra_size;
    size += fread(input + size, 1, extra_size, stdin);
    if (size < max_size) break;
  }
  if (ferror(stdin)) goto Error;
  *data = input;
  *data_size = size;
  return 1;

 Error:
  free(input);
  fprintf(stderr, "Could not read from stdin\n");
  return 0;
}
