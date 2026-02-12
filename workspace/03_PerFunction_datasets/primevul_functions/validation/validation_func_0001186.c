char * ap_php_conv_10(register int64_t num, register bool is_unsigned,
                      register int * is_negative, char *buf_end,
                      register int *len) {
  register char *p = buf_end;
  register uint64_t magnitude;

  if (is_unsigned) {
    magnitude = (uint64_t) num;
    *is_negative = 0;
  } else {
    *is_negative = (num < 0);


    if (*is_negative) {
      int64_t t = num + 1;
      magnitude = ((uint64_t) - t) + 1;
    } else {
      magnitude = (uint64_t) num;
    }
  }


  do {
    register uint64_t new_magnitude = magnitude / 10;

    *--p = (char)(magnitude - new_magnitude * 10 + '0');
    magnitude = new_magnitude;
  }
  while (magnitude);

  *len = buf_end - p;
  return (p);
}
