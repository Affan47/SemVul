String HHVM_FUNCTION(nl2br,
                     const String& str,
                     bool is_xhtml ) {
  if (str.empty()) {
    return str;
  }
  String htmlType;

  if (is_xhtml) {
    htmlType = s_br;
  } else {
    htmlType = s_non_xhtml_br;
  }

  return stringForEachBuffered(
    str.size(), str,
    [&](StringBuffer& ret, const char*& src, const char* ) {


      switch (*src) {
        case '\n':
          ret.append(htmlType);

          if (*(src + 1) == '\r') {
            ret.append(*src);
            ++src;
          }
          ret.append(*src);
          break;
        case '\r':
          ret.append(htmlType);

          if (*(src + 1) == '\n') {
            ret.append(*src);
            ++src;
          }

        default: ret.append(*src);
      }
    });
}
