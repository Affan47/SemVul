my_xml_error_lineno(MY_XML_PARSER *p)
{
  uint res=0;
  const char *s;
  for (s=p->beg ; s<p->cur; s++)
  {
    if (s[0] == '\n')
      res++;
  }
  return res;
}
