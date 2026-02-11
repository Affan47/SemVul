empty_list (void)
{
  DECLARE_STRINGSBUF (ret);

  if (end_stringsbuf (&ret) == -1)
    return NULL;

  return ret.argv;
}
