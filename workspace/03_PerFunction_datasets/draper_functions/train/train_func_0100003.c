__wctype_l (const char *property, __locale_t locale)
{
  const char *names;
  unsigned int result;
  size_t proplen = strlen (property);
  size_t i;

  names = locale->__locales[LC_CTYPE]->values[_NL_ITEM_INDEX (_NL_CTYPE_CLASS_NAMES)].string;
  for (result = 0; ; result++)
    {
      size_t nameslen = strlen (names);

      if (proplen == nameslen && memcmp (property, names, proplen) == 0)
	break;

      names += nameslen + 1;
      if (names[0] == '\0')
	return 0;
    }

  i = locale->__locales[LC_CTYPE]->values[_NL_ITEM_INDEX (_NL_CTYPE_CLASS_OFFSET)].word + result;
  return (wctype_t) locale->__locales[LC_CTYPE]->values[i].string;
}
