String StringUtil::HtmlDecode(const String& input, QuoteStyle quoteStyle,
                              const char *charset, bool all) {
  if (input.empty()) return input;

  assert(charset);

  int len = input.size();
  char *ret = string_html_decode(input.data(), len,
                                 quoteStyle != QuoteStyle::No,
                                 quoteStyle == QuoteStyle::Both,
                                 charset, all);
  if (!ret) {

    throw_not_implemented(charset);

  }

  return String(ret, len, AttachString);
}
