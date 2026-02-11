PrintWideCharsAsStringTo(const wchar_t* begin, size_t len,
                                     ostream* os) {
  *os << "L\"";
  bool is_previous_hex = false;
  for (size_t index = 0; index < len; ++index) {
    const wchar_t cur = begin[index];
    if (is_previous_hex && isascii(cur) && IsXDigit(static_cast<char>(cur))) {


      *os << "\" L\"";
    }
    is_previous_hex = PrintAsWideStringLiteralTo(cur, os) == kHexEscape;
  }
  *os << "\"";
}
