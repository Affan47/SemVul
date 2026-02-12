one_pattern_match(uschar *name, int slen, BOOL has_addresses, uschar *pattern)
{
BOOL yield = FALSE;
header_line *h;
const pcre *re = NULL;


if (*pattern == '^') re = regex_must_compile(pattern, TRUE, FALSE);


for (h = header_list; !yield && h != NULL; h = h->next)
  {
  if (h->type == htype_old || slen > h->slen ||
      strncmpic(name, h->text, slen) != 0)
    continue;


  if (has_addresses)
    {
    uschar *s = h->text + slen;

    while (!yield && *s != 0)
      {
      uschar *error, *next;
      uschar *e = parse_find_address_end(s, FALSE);
      int terminator = *e;
      int start, end, domain;


      *e = 0;
      next = parse_extract_address(s, &error, &start, &end, &domain, FALSE);
      *e = terminator;


      s = e;
      if (*s == ',') s++;


      if (next == NULL) break;


      yield = (re == NULL)?
        (strcmpic(next, pattern) == 0)
        :
        (pcre_exec(re, NULL, CS next, Ustrlen(next), 0, PCRE_EOPT, NULL, 0)
          >= 0);
      }
    }


  else
    {
    yield = (re == NULL)?
      (strstric(h->text, pattern, FALSE) != NULL)
      :
      (pcre_exec(re, NULL, CS h->text, h->slen, 0, PCRE_EOPT, NULL, 0) >= 0);
    }
  }

return yield;
}
