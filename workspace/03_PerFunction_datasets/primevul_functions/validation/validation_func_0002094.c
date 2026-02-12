bool parseRawString(int* len) {
    assertx(p[-1] == '"');
    *len = 0;
    auto const charTop = reinterpret_cast<signed char*>(top);
    for (signed char ch = *p++; ch != '\"'; ch = *p++) {
      charTop[(*len)++] = ch;
      if (ch < ' ') {

        return false;
      } else if (ch == '\\') {
        if (!handleBackslash(charTop[*len - 1])) return false;
      }
    }
    return true;
  }
