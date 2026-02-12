String HHVM_FUNCTION(html_entity_decode,
                     const String& str,
                     int flags ,
                     const String& charset ) {
  const char *scharset = charset.data();
  if (!*scharset) scharset = "ISO-8859-1";
  return StringUtil::HtmlDecode(str, StringUtil::toQuoteStyle(flags),
                                scharset, true);
}
