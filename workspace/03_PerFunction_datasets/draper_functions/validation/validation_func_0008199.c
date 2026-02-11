_opNumber(uint32_t op, uint64_t i, uint32_t base, size_t width, uint32_t flags) {
  if (base < 2 || base > 36)
    base = 10;

  char buf[128];
  char* p = buf + ASMJIT_ARRAY_SIZE(buf);

  uint64_t orig = i;
  char sign = '\0';


  if ((flags & kStringFormatSigned) != 0 && static_cast<int64_t>(i) < 0) {
    i = static_cast<uint64_t>(-static_cast<int64_t>(i));
    sign = '-';
  }
  else if ((flags & kStringFormatShowSign) != 0) {
    sign = '+';
  }
  else if ((flags & kStringFormatShowSpace) != 0) {
    sign = ' ';
  }


  do {
    uint64_t d = i / base;
    uint64_t r = i % base;

    *--p = StringBuilder_numbers[r];
    i = d;
  } while (i);

  size_t numberLength = (size_t)(buf + ASMJIT_ARRAY_SIZE(buf) - p);


  if ((flags & kStringFormatAlternate) != 0) {
    if (base == 8) {
      if (orig != 0)
        *--p = '0';
    }
    if (base == 16) {
      *--p = 'x';
      *--p = '0';
    }
  }


  if (sign != 0)
    *--p = sign;

  if (width > 256)
    width = 256;

  if (width <= numberLength)
    width = 0;
  else
    width -= numberLength;


  size_t prefixLength = (size_t)(buf + ASMJIT_ARRAY_SIZE(buf) - p) - numberLength;
  char* data = prepare(op, prefixLength + width + numberLength);

  if (data == NULL)
    return false;

  ::memcpy(data, p, prefixLength);
  data += prefixLength;

  ::memset(data, '0', width);
  data += width;

  ::memcpy(data, p + prefixLength, numberLength);
  return true;
}
