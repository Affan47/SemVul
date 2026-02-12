Variant HHVM_FUNCTION(mb_encode_numericentity,
                      const String& str,
                      const Variant& convmap,
                      const Variant& opt_encoding ,
                      bool is_hex ) {
  const String encoding = convertArg(opt_encoding);
  return php_mb_numericentity_exec(str, convmap, encoding, is_hex, 0);
}
