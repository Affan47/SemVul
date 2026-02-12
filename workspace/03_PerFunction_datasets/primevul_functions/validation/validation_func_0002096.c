bool parseNumber(char firstChar, bool array_elem = false) {
    uint64_t x = 0;
    bool neg = false;
    const char* begin = p - 1;
    if (firstChar == '-') {
      neg = true;
    } else {
      x = firstChar - '0';
    }

    while (*p >= '0' && *p <= '9') {
      x = (x * 10) + (*p - '0');
      ++p;
    }
    if (*p == '.' || *p == 'e' || *p == 'E') {
      pushDouble(zend_strtod(begin, &p));
      return true;
    }

    auto len = p - begin;


    if (UNLIKELY(len > 1 && firstChar == '0' && array_elem)) {
      return false;
    }


    if (LIKELY(len < 19) || (len == 19 && firstChar <= '8')) {
      int64_t sx = x;
      pushInt64(neg ? -sx : sx);
    } else {
      parseBigInt(len);
    }
    return true;
  }
