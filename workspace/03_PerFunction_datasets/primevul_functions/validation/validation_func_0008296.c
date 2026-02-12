static bool get_run(const uint8_t* ip, const uint8_t* ip_bound) {
  uint8_t x = *ip;
  int64_t value, value2;

  memset(&value, x, 8);
  while (ip < (ip_bound - 8)) {
#if defined(BLOSC_STRICT_ALIGN)
    memcpy(&value2, ref, 8);
#else
    value2 = *(int64_t*)ip;
#endif
    if (value != value2) {

      return false;
    }
    else {
      ip += 8;
    }
  }

  while ((ip < ip_bound) && (*ip == x)) ip++;
  return ip == ip_bound ? true : false;
}
