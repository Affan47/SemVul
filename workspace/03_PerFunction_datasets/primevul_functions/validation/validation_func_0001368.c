Variant strpbrk_char_list_has_nulls_slow(const String& haystack,
                                         const String& char_list) {

  auto const charListSz = char_list.size();
  auto const charListData = char_list.c_str();
  assertx(memchr(charListData, '\0', charListSz) != nullptr);


  auto charListWithoutNull = (char*) req::malloc_noptrs(charListSz);
  SCOPE_EXIT { req::free(charListWithoutNull); };

  auto copy_ptr = charListWithoutNull;
  auto const charListStop = charListData + char_list.size();
  for (auto ptr = charListData; ptr != charListStop; ++ptr) {
    if (*ptr != '\0') { *copy_ptr++ = *ptr; }
  }
  assertx((copy_ptr - charListWithoutNull) < charListSz);

  *copy_ptr = '\0';


  auto haySize = haystack.size();
  auto hayData = haystack.c_str();

  size_t idx = strcspn(hayData, charListWithoutNull);
  if (idx < haySize) {


    if (existence_only) { return true; }
    return String(hayData + idx, haySize - idx, CopyString);
  }
  return false;
}
