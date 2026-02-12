Variant preg_grep(const String& pattern, const Array& input, int flags ) {
  PCRECache::Accessor accessor;
  if (!pcre_get_compiled_regex_cache(accessor, pattern.get())) {
    return preg_return_bad_regex_error(false);
  }
  const pcre_cache_entry* pce = accessor.get();

  int size_offsets = 0;
  int* offsets = create_offset_array(pce, size_offsets);
  if (offsets == nullptr) {
    return preg_return_internal_error(false);
  }
  SmartFreeHelper freer(offsets);

  const bool hackArrOutput = flags & PREG_FB_HACK_ARRAYS;


  auto ret = hackArrOutput ? Array::CreateDict() : Array::CreateDArray();


  bool invert = (flags & PREG_GREP_INVERT);
  pcre_extra extra;
  init_local_extra(&extra, pce->extra);

  for (ArrayIter iter(input); iter; ++iter) {
    String entry = iter.second().toString();


    int count = pcre_exec(pce->re, &extra, entry.data(), entry.size(),
                          0, 0, offsets, size_offsets);


    if (count == 0) {
      raise_warning("Matched, but too many substrings");
      count = size_offsets / 3;
    } else if (count < 0 && count != PCRE_ERROR_NOMATCH) {
      if (pcre_need_log_error(count)) {
        pcre_log_error(__FUNCTION__, __LINE__, count,
                       pattern.data(), pattern.size(),
                       entry.data(), entry.size(),
                       "", 0,
                       flags);
      }

      return preg_return_pcre_error(count, std::move(ret));
    }


    if ((count > 0 && !invert) ||
        (count == PCRE_ERROR_NOMATCH && invert)) {


      ret.set(iter.first(), entry);
    }
  }

  return preg_return_no_error(std::move(ret));
}
