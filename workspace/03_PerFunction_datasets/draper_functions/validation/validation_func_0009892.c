store_decimal(const my_decimal *d)
{
  char buff[DECIMAL_MAX_STR_LENGTH+1];
  String str(buff, sizeof(buff), &my_charset_numeric);
  my_decimal2string(E_DEC_FATAL_ERROR, d, 0, 0, 0, &str);
  return store(str.ptr(), str.length(), str.charset());
}
