static Variant php_pcre_replace(const String& pattern, const String& subject,
                                const Variant& replace_var, bool callable,
                                int limit, int* replace_count) {
  PCRECache::Accessor accessor;
  if (!pcre_get_compiled_regex_cache(accessor, pattern.get())) {
    return preg_return_bad_regex_error(init_null());
  }
  const pcre_cache_entry* pce = accessor.get();
  if (pce->preg_options & PREG_REPLACE_EVAL) {
    raise_error("preg_replace(): Support for the /e modifier has been removed, use "
                "preg_replace_callback instead");
  }

  int size_offsets;
  int* offsets = create_offset_array(pce, size_offsets);
  SmartFreeHelper offsetsFreer(offsets);
  if (offsets == nullptr) {
    return preg_return_internal_error(init_null());
  }

  const char* const* subpat_names = get_subpat_names(pce);
  if (subpat_names == nullptr) {
    return preg_return_internal_error(init_null());
  }

  const char* replace = nullptr;
  const char* replace_end = nullptr;
  int replace_len = 0;
  String replace_val;

  if (!callable) {
    replace_val = replace_var.toString();
    replace = replace_val.data();
    replace_len = replace_val.size();
    replace_end = replace + replace_len;
  }

  StringBuffer result(2 * subject.size());

  try {


    const char* match = nullptr;
    int start_offset = 0;
    pcre_extra extra;
    init_local_extra(&extra, pce->extra);

    const char* walk;
    char walk_last;
    int match_len;
    int backref;
    int g_notempty = 0;
    int exec_options = 0;
    while (1) {

      int count = pcre_exec(pce->re, &extra, subject.data(), subject.size(),
                            start_offset,
                            exec_options | g_notempty,
                            offsets, size_offsets);


      exec_options |= PCRE_NO_UTF8_CHECK;


      if (count == 0) {
        raise_warning("Matched, but too many substrings");
        count = size_offsets / 3;
      }

      const char* piece = subject.data() + start_offset;
      if (count > 0 && offsets[1] >= offsets[0] &&
          (limit == -1 || limit > 0)) {
        if (replace_count) {
          ++*replace_count;
        }

        match = subject.data() + offsets[0];

        String callable_result;
        if (callable) {

          callable_result = preg_do_repl_func(replace_var, subject, offsets,
                                              subpat_names, count);
        } else {
          walk = replace;
          walk_last = 0;
          while (walk < replace_end) {
            if ('\\' == *walk || '$' == *walk) {
              if (walk_last == '\\') {
                walk++;
                walk_last = 0;
                continue;
              }
              if (preg_get_backref(&walk, &backref)) {
                if (backref < count) {
                  match_len = offsets[(backref<<1)+1] - offsets[backref<<1];
                }
                continue;
              }
            }
            walk++;
            walk_last = walk[-1];
          }
        }


        result.append(piece, match-piece);


        int result_len = result.size();

        if (callable) {

          result.append(callable_result.data(), callable_result.size());
          result_len += callable_result.size();
        } else {
          walk = replace;
          walk_last = 0;
          Array params;
          while (walk < replace_end) {
            if ('\\' == *walk || '$' == *walk) {
              if (walk_last == '\\') {
                result.set(result.size() - 1, *walk++);
                walk_last = 0;
                continue;
              }
              if (preg_get_backref(&walk, &backref)) {
                if (backref < count) {
                  match_len = offsets[(backref<<1)+1] - offsets[backref<<1];
                  result.append(
                    subject.data() + offsets[backref<<1],
                    match_len
                  );
                }
                continue;
              }
            }
            result.append(*walk++);
            walk_last = walk[-1];
          }
        }

        if (limit != -1) {
          limit--;
        }

      } else if (count == PCRE_ERROR_NOMATCH || limit == 0) {


        if (g_notempty != 0 && start_offset < subject.size()) {
          offsets[0] = start_offset;
          offsets[1] = start_offset + 1;
          result.append(piece, 1);
        } else {

          result.append(piece, subject.size() - start_offset);
          break;
        }
      } else {
        if (pcre_need_log_error(count)) {
          const char* s;
          int size;
          String stemp;
          if (callable) {
            if (replace_var.isObject()) {
              stemp = replace_var.asCObjRef()->getClassName().asString()
                    + "::__invoke";
            } else {
              stemp = replace_var.toString();
            }
            s = stemp.data();
            size = stemp.size();
          } else {
            s = replace_val.data();
            size = replace_val.size();
          }
          pcre_log_error(__FUNCTION__, __LINE__, count,
                         pattern.data(), pattern.size(),
                         subject.data(), subject.size(),
                         s, size,
                         callable, limit, start_offset, g_notempty);
        }
        return preg_return_pcre_error(count, init_null());
      }


      g_notempty = (offsets[1] == offsets[0])? PCRE_NOTEMPTY | PCRE_ANCHORED : 0;


      start_offset = offsets[1];
    }

    return preg_return_no_error(result.detach());
  } catch (...) {
    throw;
  }
}
