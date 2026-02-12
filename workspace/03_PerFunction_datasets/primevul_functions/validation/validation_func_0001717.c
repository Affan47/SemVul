String HHVM_FUNCTION(fb_htmlspecialchars,
                     const String& str,
                     int flags ,
                     const String& charset ,
                     const Variant& extra ) {
  if (!extra.isNull() && !extra.isArray()) {
    raise_expected_array_warning("fb_htmlspecialchars");
  }
  const Array& arr_extra = extra.isNull() ? empty_varray() : extra.toArray();
  return StringUtil::HtmlEncodeExtra(str, StringUtil::toQuoteStyle(flags),
                                     charset.data(), false, arr_extra);
}
