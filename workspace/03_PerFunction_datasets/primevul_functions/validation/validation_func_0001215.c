Variant preg_match_all(const String& pattern, const String& subject,
                       Variant* matches ,
                       int flags , int offset ) {
  return preg_match_all(pattern.get(), subject.get(), matches, flags, offset);
}
