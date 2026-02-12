string_nextinlist(const uschar **listptr, int *separator, uschar *buffer, int buflen)
{
int sep = *separator;
const uschar *s = *listptr;
BOOL sep_is_special;

if (s == NULL) return NULL;


while (isspace(*s) && *s != sep) s++;


if (sep <= 0)
  {
  if (*s == '<' && (ispunct(s[1]) || iscntrl(s[1])))
    {
    sep = s[1];
    s += 2;
    while (isspace(*s) && *s != sep) s++;
    }
  else
    {
    sep = (sep == 0)? ':' : -sep;
    }
  *separator = sep;
  }


if (*s == 0) return NULL;


sep_is_special = iscntrl(sep);


if (buffer)
  {
  int p = 0;
  for (; *s != 0; s++)
    {
    if (*s == sep && (*(++s) != sep || sep_is_special)) break;
    if (p < buflen - 1) buffer[p++] = *s;
    }
  while (p > 0 && isspace(buffer[p-1])) p--;
  buffer[p] = 0;
  }


else
  {
  const uschar *ss;
  gstring * g = NULL;


  if (*s == sep)
    {
    s++;
    if (*s != sep || sep_is_special)
      {
      *listptr = s;
      return string_copy(US"");
      }
    }


  for (;;)
    {
    for (ss = s + 1; *ss != 0 && *ss != sep; ss++) ;
    g = string_catn(g, s, ss-s);
    s = ss;
    if (*s == 0 || *(++s) != sep || sep_is_special) break;
    }
  while (g->ptr > 0 && isspace(g->s[g->ptr-1])) g->ptr--;
  buffer = string_from_gstring(g);
  gstring_reset_unused(g);
  }


*listptr = s;
return buffer;
}
