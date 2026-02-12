String HHVM_FUNCTION(md5,
                     const String& str,
                     bool raw_output ) {
  return StringUtil::MD5(str, raw_output);
}
