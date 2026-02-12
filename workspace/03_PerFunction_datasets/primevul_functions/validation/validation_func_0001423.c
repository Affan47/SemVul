Variant preg_match(const StringData* pattern, const StringData* subject,
                   Variant* matches , int flags ,
                   int offset ) {
  return preg_match_impl(pattern, subject, matches, flags, offset, false);
}
