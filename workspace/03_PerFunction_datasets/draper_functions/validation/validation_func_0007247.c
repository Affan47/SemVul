filename_pos(const string_type & str,
                          size_type end_pos)

  {

    if (end_pos == 2
      && is_separator(str[0])
      && is_separator(str[1])) return 0;


    if (end_pos && is_separator(str[end_pos-1]))
      return end_pos-1;


    size_type pos(str.find_last_of(separators, end_pos-1));

#   ifdef BOOST_WINDOWS_API
    if (pos == string_type::npos)
      pos = str.find_last_of(colon, end_pos-2);
#   endif

    return (pos == string_type::npos
      || (pos == 1 && is_separator(str[0])))
        ? 0
        : pos + 1;
  }
