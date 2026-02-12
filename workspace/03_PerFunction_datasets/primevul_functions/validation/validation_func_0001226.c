Variant str_replace(const Variant& search, const Variant& replace,
                    const Variant& subject, int64_t& count) {
  Variant ret;
  count = 0;
  if (LIKELY(search.isString() && replace.isString() && subject.isString())) {
    int icount;

    ret = string_replace(subject.asCStrRef(), search.asCStrRef(),
                         replace.asCStrRef(), icount, true);
    count = icount;
  } else {


    ret = str_replace(search, replace, subject, count, true);
  }
  return ret;
}
