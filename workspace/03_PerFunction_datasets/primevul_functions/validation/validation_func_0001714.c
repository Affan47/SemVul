String HHVM_FUNCTION(rtrim,
                     const String& str,
                     const String& charlist ) {
  return stringTrim<false,true>(str, charlist);
}
