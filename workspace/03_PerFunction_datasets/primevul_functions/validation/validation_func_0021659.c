parse_grep_colors (void)
{
  const char *p;
  char *q;
  char *name;
  char *val;

  p = getenv ("GREP_COLORS");
  if (p == NULL || *p == '\0')
    return;


  q = xstrdup (p);

  name = q;
  val = NULL;

  for (;;)
    if (*q == ':' || *q == '\0')
      {
        char c = *q;
        struct color_cap const *cap;

        *q++ = '\0';


        for (cap = color_dict; cap->name; cap++)
          if (STREQ (cap->name, name))
            break;

        if (cap->var && val)
          *(cap->var) = val;
        if (cap->fct)
          cap->fct ();
        if (c == '\0')
          return;
        name = q;
        val = NULL;
      }
    else if (*q == '=')
      {
        if (q == name || val)
          return;
        *q++ = '\0';
        val = q;
      }
    else if (val == NULL)
      q++;
    else if (*q == ';' || (*q >= '0' && *q <= '9'))
      q++;
    else
      return;
}
