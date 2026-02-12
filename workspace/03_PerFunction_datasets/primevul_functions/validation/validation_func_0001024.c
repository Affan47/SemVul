Variant preg_match(const String& pattern, const String& subject,
                   Variant* matches , int flags ,
                   int offset ) {
  return preg_match(pattern.get(), subject.get(), matches, flags, offset);
}
