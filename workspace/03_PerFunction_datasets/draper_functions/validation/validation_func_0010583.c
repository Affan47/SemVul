decodeHow (
	char	*how)
{
  if (mctx.mode & VERY_VERBOSE)
    printf ("decodeHow: how=\"%s\"\n", how);

  if (!strcmp (how, "INCRFROMFILE"))		return (HOW_INCR_FROM_FILE);
  if (!strcmp (how, "INCRFROMFILENOLOOP"))	return (HOW_INCR_FROM_FILE_NL);
  if (!strcmp (how, "INCRN"))			return (HOW_INCR_NB);
  if (!strcmp (how, "INCRNNOLOOP"))		return (HOW_INCR_NB_NOLOOP);
  if (!strcmp (how, "RNDFROMFILE"))		return (HOW_RND_FROM_FILE);
  if (!strcmp (how, "RNDN"))			return (HOW_RND_NUMBER);
  if (!strcmp (how, "RNDS"))			return (HOW_RND_STRING);
  return (-1);
}
