trim(const std::string& str, const char *sep) {
    if (sep == NULL)
      sep = kBlankChars;
    std::string::size_type const first = str.find_first_not_of(sep);
    return (first == std::string::npos) ? std::string() : str.substr(first, str.find_last_not_of(sep) - first + 1);
  }
