unsigned parse_nonnegative_int(const Char *&s) {
  assert('0' <= *s && *s <= '9');
  unsigned value = 0;

  unsigned max_int = (std::numeric_limits<int>::max)();
  unsigned big = max_int / 10;
  do {

    if (value > big) {
      value = max_int + 1;
      break;
    }
    value = value * 10 + (*s - '0');
    ++s;
  } while ('0' <= *s && *s <= '9');

  if (value > max_int)
    FMT_THROW(FormatError("number is too big"));
  return value;
}
