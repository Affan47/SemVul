String preg_quote(const String& str,
                  const String& delimiter ) {
  const char* in_str = str.data();
  const char* in_str_end = in_str + str.size();


  if (in_str == in_str_end) {
    return str;
  }

  char delim_char = 0;
  bool quote_delim = false;
  if (!delimiter.empty()) {
    delim_char = delimiter.charAt(0);
    quote_delim = true;
  }


  static_assert(
    (StringData::MaxSize * 4 + 1) < std::numeric_limits<int64_t>::max()
  );
  String ret(4 * str.size() + 1, ReserveString);
  char* out_str = ret.mutableData();


  const char* p;
  char* q;
  for (p = in_str, q = out_str; p != in_str_end; p++) {
    char c = *p;
    switch (c) {
    case '.': case '\\': case '+': case '*': case '?':
    case '[': case '^':  case ']': case '$': case '(':
    case ')': case '{':  case '}': case '=': case '!':
    case '>': case '<':  case '|': case ':': case '-':
    case '#':
      *q++ = '\\';
      *q++ = c;
      break;

    case '\0':
      *q++ = '\\';
      *q++ = '0';
      *q++ = '0';
      *q++ = '0';
      break;

    default:
      if (quote_delim && c == delim_char)
        *q++ = '\\';
      *q++ = c;
      break;
    }
  }
  *q = '\0';

  return ret.setSize(q - out_str);
}
