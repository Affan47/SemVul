void Item_uint::print(String *str, enum_query_type query_type)
{

  str_value.set((ulonglong) value, default_charset());
  str->append(str_value);
}
