String HHVM_FUNCTION(htmlspecialchars,
                     const String& str,
                     int flags ,
                     const String& charset ,
                     bool double_encode ) {

  const char *scharset = charset.data();
  if (!*scharset) scharset = "ISO-8859-1";
  return StringUtil::HtmlEncode(str, StringUtil::toQuoteStyleBitmask(flags),
                                scharset, double_encode, false);
}
