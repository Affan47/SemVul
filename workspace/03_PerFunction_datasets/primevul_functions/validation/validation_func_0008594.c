XML_SetReturnNSTriplet(XML_Parser parser, int do_nst)
{
  if (parser == NULL)
    return;

  if (ps_parsing == XML_PARSING || ps_parsing == XML_SUSPENDED)
    return;
  ns_triplets = do_nst ? XML_TRUE : XML_FALSE;
}
