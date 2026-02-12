pcre_literal_data::pcre_literal_data(const char* pattern, int coptions) {
  if (coptions & ~PCRE_CASELESS) {
    return;
  }

  auto p = pattern;
  if (*p == '^') {
    match_start = true;
    p++;
  }

  std::string pattern_buffer;
  while (isalnum((unsigned char)*p) || (*p && strchr("/\\ :-_", *p))) {


    if (*p == '\\') {
      if (!p[1] || isalnum((unsigned char)p[1])) {
        break;
      } else {
        p++;
      }
    }
    pattern_buffer += *p++;
  }
  if (*p == '$') {
    match_end = true;
    p++;
  }
  if (!*p) {

    case_insensitive = coptions & PCRE_CASELESS;
    literal_str = std::move(pattern_buffer);
  }
}
