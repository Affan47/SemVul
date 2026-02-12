String HHVM_FUNCTION(ltrim,
                     const String& str,
                     const String& charlist ) {
  return stringTrim<true,false>(str, charlist);
}
