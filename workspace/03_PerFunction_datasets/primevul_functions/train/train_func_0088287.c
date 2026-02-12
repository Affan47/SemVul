bool parse(const char *s, any &dt, T &val,
             const char *  = nullptr) const {
    auto n = strlen(s);
    return parse_n(s, n, dt, val);
  }
