eet_data_put_string(Eet_Dictionary *ed,
                    const void     *src,
                    int            *size_ret)
{
   char *s, *d;
   int len;

   if (ed)
     {
        const char *str;
        int idx;

        str = *((const char **)src);
        if (!str)
          return NULL;

        idx = eet_dictionary_string_add(ed, str);
        if (idx == -1)
          return NULL;

        return eet_data_put_int(ed, &idx, size_ret);
     }

   s = (char *)(*((char **)src));
   if (!s)
     return NULL;

   len = strlen(s);
   d = malloc(len + 1);
   if (!d)
     return NULL;

   memcpy(d, s, len + 1);
   *size_ret = len + 1;
   return d;
}
