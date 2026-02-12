String string_pad(const char *input, int len, int pad_length,
                  const char *pad_string, int pad_str_len,
                  int pad_type) {
  assert(input);
  int num_pad_chars = pad_length - len;


  if (pad_length < 0 || num_pad_chars < 0) {
    return String(input, len, CopyString);
  }


  if (pad_str_len == 0) {
    throw_invalid_argument("pad_string: (empty)");
    return String();
  }

  String ret(pad_length, ReserveString);
  char *result = ret.bufferSlice().ptr;


  int left_pad, right_pad;
  switch (pad_type) {
  case STR_PAD_RIGHT:
    left_pad = 0;
    right_pad = num_pad_chars;
    break;
  case STR_PAD_LEFT:
    left_pad = num_pad_chars;
    right_pad = 0;
    break;
  case STR_PAD_BOTH:
    left_pad = num_pad_chars / 2;
    right_pad = num_pad_chars - left_pad;
    break;
  default:
    throw_invalid_argument("pad_type: %d", pad_type);
    return String();
  }


  int result_len = 0;
  for (int i = 0; i < left_pad; i++) {
    result[result_len++] = pad_string[i % pad_str_len];
  }


  memcpy(result + result_len, input, len);
  result_len += len;


  for (int i = 0; i < right_pad; i++) {
    result[result_len++] = pad_string[i % pad_str_len];
  }
  ret.setSize(result_len);
  return ret;
}
