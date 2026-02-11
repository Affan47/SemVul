opt_nocharconv(Jconf *jconf, char *arg[], int argnum)
{
#ifdef CHARACTER_CONVERSION
  if (from_code) free(from_code);
  if (to_code) free(to_code);
  from_code = NULL;
  to_code = NULL;
#else
  fprintf(stderr, "Warning: character set conversion disabled, option \"-nocharconv\" ignored\n");
#endif
  return TRUE;
}
