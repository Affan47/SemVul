bool Discovered_table_list::add_table(const char *tname, size_t tlen)
{


  if (wild && my_wildcmp(table_alias_charset, tname, tname + tlen, wild, wend,
                         wild_prefix, wild_one, wild_many))
      return 0;

  LEX_CSTRING *name= thd->make_clex_string(tname, tlen);
  if (!name || tables->append(name))
    return 1;
  return 0;
}
