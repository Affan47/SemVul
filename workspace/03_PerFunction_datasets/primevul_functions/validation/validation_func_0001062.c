String HHVM_FUNCTION(chop,
                      const String& str,
                      const String& charlist ) {
  return stringTrim<false,true>(str, charlist);
}
