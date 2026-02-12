static int mutt_is_autoview (BODY *b)
{
  char type[STRING];
  int is_autoview = 0;

  snprintf (type, sizeof (type), "%s/%s", TYPE (b), b->subtype);

  if (option(OPTIMPLICITAUTOVIEW))
  {

    is_autoview = 1;
  }
  else
  {

    LIST *t = AutoViewList;

    mutt_check_lookup_list (b, type, sizeof (type));
    for (; t; t = t->next)
    {
      int i = mutt_strlen (t->data) - 1;
      if ((i > 0 && t->data[i-1] == '/' && t->data[i] == '*' &&
           ascii_strncasecmp (type, t->data, i) == 0) ||
          ascii_strcasecmp (type, t->data) == 0)
        is_autoview = 1;
    }

    if (is_mmnoask (type))
      is_autoview = 1;
  }


  if (is_autoview)
    return rfc1524_mailcap_lookup(b, type, sizeof(type), NULL, MUTT_AUTOVIEW);

  return 0;
}
