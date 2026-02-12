string_cat(uschar *string, int *size, int *ptr, const uschar *s, int count)
{
int p = *ptr;

if (p + count >= *size)
  {
  int oldsize = *size;


  int inc = (oldsize < 4096)? 100 : 1024;
  while (*size <= p + count) *size += inc;


  if (string == NULL) string = store_get(*size);


  else if (!store_extend(string, oldsize, *size))
    {
    BOOL release_ok = store_last_get[store_pool] == string;
    uschar *newstring = store_get(*size);
    memcpy(newstring, string, p);
    if (release_ok) store_release(string);
    string = newstring;
    }
  }


memcpy(string + p, s, count);
*ptr = p + count;
return string;
}
