static Variant preg_match_impl(const StringData* pattern,
                               const StringData* subject,
                               Variant* subpats, int flags, int start_offset,
                               bool global) {
  PCRECache::Accessor accessor;
  if (!pcre_get_compiled_regex_cache(accessor, pattern)) {
    return preg_return_bad_regex_error(false);
  }
  const pcre_cache_entry* pce = accessor.get();

  const bool hackArrOutput = flags & PREG_FB_HACK_ARRAYS;
  const bool includeNonMatchingCaptures = flags & PREG_FB__PRIVATE__HSL_IMPL;

  pcre_extra extra;
  init_local_extra(&extra, pce->extra);
  if (subpats) {
    *subpats = hackArrOutput ? Array::CreateDict() : Array::CreateDArray();
  }
  int exec_options = 0;

  int subpats_order = global ? PREG_PATTERN_ORDER : 0;
  bool offset_capture = false;
  if (flags) {
    offset_capture = flags & PREG_OFFSET_CAPTURE;


    if (flags & 0xff) {
      subpats_order = flags & 0xff;
    }
    if ((global && (subpats_order < PREG_PATTERN_ORDER ||
                    subpats_order > PREG_SET_ORDER)) ||
        (!global && subpats_order != 0)) {
      raise_warning("Invalid flags specified");
      return preg_return_internal_error(init_null());
    }
  }


  if (start_offset < 0) {
    start_offset = subject->size() + start_offset;
    if (start_offset < 0) {
      start_offset = 0;
    }
  }

  int size_offsets = 0;
  int* offsets = create_offset_array(pce, size_offsets);
  SmartFreeHelper offsetsFreer(offsets);
  int num_subpats = size_offsets / 3;
  if (offsets == nullptr) {
    return preg_return_internal_error(false);
  }

  const char* const* subpat_names = get_subpat_names(pce);
  if (subpat_names == nullptr) {
    return preg_return_internal_error(false);
  }


  auto match_sets = hackArrOutput ? Array::CreateDict() : Array::CreateDArray();
  if (global && subpats_order == PREG_PATTERN_ORDER) {
    for (int i = 0; i < num_subpats; i++) {
      match_sets.set(i,
        hackArrOutput ? Array::CreateDict() : Array::CreateDArray());
    }
  }

  int matched = 0;

  int g_notempty = 0;
  const char** stringlist;
  int i;
  do {

    int count = 0;


    if (pce->literal_data && !global) {
      assertx(pce->literal_data->isLiteral());


      count = pce->literal_data->matches(subject, start_offset, offsets) ? 1
        : PCRE_ERROR_NOMATCH;
    } else {

      count = pcre_exec(pce->re, &extra, subject->data(), subject->size(),
                        start_offset,
                        exec_options | g_notempty,
                        offsets, size_offsets);


      exec_options |= PCRE_NO_UTF8_CHECK;
    }

    if (count == 0) {
      raise_warning("Matched, but too many substrings");
      count = size_offsets / 3;
    }


    if (count > 0) {
      matched++;

      if (subpats) {

        if (offsets[1] < offsets[0] ||
            pcre_get_substring_list(subject->data(), offsets, count,
                                    &stringlist) < 0) {
          raise_warning("Get subpatterns list failed");
          return preg_return_internal_error(false);
        }

        if (global) {
          if (subpats_order == PREG_PATTERN_ORDER) {

            for (i = 0; i < count; i++) {
              auto const length = offsets[(i<<1)+1] - offsets[i<<1];
              auto const match = String(stringlist[i], length, CopyString);
              auto const value = offset_capture
                ? Variant(str_offset_pair(match, offsets[i<<1], hackArrOutput))
                : Variant(match);
              auto& arr = asArrRef(match_sets.lval(i));
              assertx(arr->isVectorData());
              arr.set(safe_cast<int64_t>(arr.size()), value);
            }


            if (count < num_subpats) {
              for (; i < num_subpats; i++) {
                auto& arr = asArrRef(match_sets.lval(i));
                assertx(arr->isVectorData());
                arr.set(safe_cast<int64_t>(arr.size()), empty_string());
              }
            }
          } else {
            auto result_set = hackArrOutput
              ? Array::CreateDict()
              : Array::CreateDArray();


            for (i = 0; i < count; i++) {
              auto const length = offsets[(i<<1)+1] - offsets[i<<1];
              auto const match = String(stringlist[i], length, CopyString);
              auto const value = offset_capture
                ? Variant(str_offset_pair(match, offsets[i<<1], hackArrOutput))
                : Variant(match);
              if (subpat_names[i]) {
                result_set.set(String(subpat_names[i]), value);
              }
              result_set.set(i, value);
            }
            if (includeNonMatchingCaptures && count < num_subpats) {
              auto const match = empty_string();
              for (; i < num_subpats; i++) {
                auto const value = offset_capture
                  ? Variant(str_offset_pair(match, offsets[i<<1], hackArrOutput))
                  : Variant(match);
                if (subpat_names[i]) {
                  result_set.set(String(subpat_names[i]), value);
                }
                result_set.set(i, value);
              }
            }

            auto& arr = subpats->asArrRef();
            assertx(arr->isVectorData());
            arr.set(safe_cast<int64_t>(arr.size()), std::move(result_set));
          }
        } else {

          auto& arr = subpats->asArrRef();
          for (i = 0; i < count; i++) {
            auto const length = offsets[(i<<1)+1] - offsets[i<<1];
            auto const match = String(stringlist[i], length, CopyString);
            auto const value = offset_capture
              ? Variant(str_offset_pair(match, offsets[i<<1], hackArrOutput))
              : Variant(match);
            if (subpat_names[i]) {
              arr.set(String(subpat_names[i]), value);
            }
            arr.set(i, value);
          }
          if (includeNonMatchingCaptures && count < num_subpats) {
            auto const match = empty_string();
            for (; i < num_subpats; i++) {
              auto const value = offset_capture
                ? Variant(str_offset_pair(match, offsets[i<<1], hackArrOutput))
                : Variant(match);
              if (subpat_names[i]) {
                arr.set(String(subpat_names[i]), value);
              }
              arr.set(i, value);
            }
          }
        }
        pcre_free((void *) stringlist);
      }
    } else if (count == PCRE_ERROR_NOMATCH) {


      if (g_notempty && start_offset < subject->size()) {
        offsets[0] = start_offset;
        offsets[1] = start_offset + 1;
      } else
        break;
    } else {
      if (pcre_need_log_error(count)) {
        pcre_log_error(__FUNCTION__, __LINE__, count,
                       pattern->data(), pattern->size(),
                       subject->data(), subject->size(),
                       "", 0,
                       flags, start_offset, g_notempty, global);
      }
      return preg_return_pcre_error(count, false);
    }


    g_notempty = (offsets[1] == offsets[0])? PCRE_NOTEMPTY | PCRE_ANCHORED : 0;


    start_offset = offsets[1];
  } while (global);


  if (subpats && global && subpats_order == PREG_PATTERN_ORDER) {
    auto& arr = subpats->asArrRef();
    for (i = 0; i < num_subpats; i++) {
      if (subpat_names[i]) {
        arr.set(String(subpat_names[i]), match_sets[i]);
      }
      arr.set(i, match_sets[i]);
    }
  }
  return preg_return_no_error(std::move(matched));
}
