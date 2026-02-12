void Item_string::print(String *str, enum_query_type query_type)
{
  const bool print_introducer=
    !(query_type & QT_WITHOUT_INTRODUCERS) && is_cs_specified();
  if (print_introducer)
  {
    str->append('_');
    str->append(collation.collation->csname);
  }

  str->append('\'');

  if (query_type & QT_TO_SYSTEM_CHARSET)
  {
    if (print_introducer)
    {


      ErrConvString tmp(str_value.ptr(), str_value.length(), &my_charset_bin);
      str->append(tmp.ptr());
    }
    else
    {
      if (my_charset_same(str_value.charset(), system_charset_info))
        str_value.print(str);
      else
      {
        THD *thd= current_thd;
        LEX_STRING utf8_lex_str;

        thd->convert_string(&utf8_lex_str,
                            system_charset_info,
                            str_value.c_ptr_safe(),
                            str_value.length(),
                            str_value.charset());

        String utf8_str(utf8_lex_str.str,
                        utf8_lex_str.length,
                        system_charset_info);

        utf8_str.print(str);
      }
    }
  }
  else
  {

    str_value.print(str);
  }

  str->append('\'');
}
