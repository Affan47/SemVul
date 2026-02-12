String HHVM_FUNCTION(htmlspecialchars_decode,
                     const String& str,
                     int flags ) {
  return StringUtil::HtmlDecode(str, StringUtil::toQuoteStyle(flags),
                                "UTF-8", false);
}
