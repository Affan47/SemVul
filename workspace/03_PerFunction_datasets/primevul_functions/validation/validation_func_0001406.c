String HHVM_FUNCTION(trim,
                     const String& str,
                     const String& charlist ) {
  return stringTrim<true,true>(str, charlist);
}
