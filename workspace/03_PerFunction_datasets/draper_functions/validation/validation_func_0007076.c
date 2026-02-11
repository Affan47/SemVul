string_comparestr(mystring_t *str1, char *str2)
{
  int str2len=strlen(str2);
  char *data1;
  char *data2;
  int lup;

  if (str1->len!=str2len) return SIEVE_FAIL;

  data1=string_DATAPTR(str1);
  data2=str2;

  for (lup=0;lup<str1->len;lup++)
    if (data1[lup]!=data2[lup])
      return SIEVE_FAIL;

  return SIEVE_OK;
}
