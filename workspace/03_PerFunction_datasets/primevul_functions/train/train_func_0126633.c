acl_getline(void)
{
uschar *yield;


for(;;)
  {
  while (isspace(*acl_text)) acl_text++;
  if (*acl_text == 0) return NULL;
  yield = acl_text;

  while (*acl_text != 0 && *acl_text != '\n') acl_text++;


  if (*acl_text == 0) return (*yield == '#')? NULL : yield;


  if (*yield != '#') break;
  }


for(;;)
  {
  uschar *cont;
  for (cont = acl_text - 1; isspace(*cont); cont--);


  if (*cont != '\\')
    {
    *acl_text++ = 0;
    return yield;
    }


  for (;;)
    {
    while (*(++acl_text) == ' ' || *acl_text == '\t');
    if (*acl_text != '#') break;
    while (*(++acl_text) != 0 && *acl_text != '\n');
    }


  memmove(cont, acl_text, acl_text_end - acl_text);
  acl_text_end -= acl_text - cont;
  acl_text = cont;
  while (*acl_text != 0 && *acl_text != '\n') acl_text++;
  if (*acl_text == 0) return yield;
  }


}
