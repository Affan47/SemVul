bool IsUrlArg(const base::CommandLine::CharType* arg) {

  auto c = *arg;
  if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
    for (auto p = arg + 1; *p; ++p) {
      c = *p;


      if (c == ':') {

        if (p == arg + 1)
          break;

        return true;
      }


      if (c == ' ' || (0x9 <= c && c <= 0xD))
        break;
    }
  }

  return false;
}
