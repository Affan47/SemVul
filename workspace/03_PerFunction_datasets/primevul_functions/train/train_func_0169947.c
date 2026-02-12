void Item_int::print(String *str, enum_query_type query_type)
{

  str_value.set_int(value, unsigned_flag, &my_charset_bin);
  str->append(str_value);
}
