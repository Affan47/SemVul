regcomp (preg, pattern, cflags)
    regex_t *_Restrict_ preg;
    const char *_Restrict_ pattern;
    int cflags;
{
  reg_errcode_t ret;
  reg_syntax_t syntax = ((cflags & REG_EXTENDED) ? RE_SYNTAX_POSIX_EXTENDED
			 : RE_SYNTAX_POSIX_BASIC);

  preg->buffer = NULL;
  preg->allocated = 0;
  preg->used = 0;


  preg->fastmap = re_malloc (char, SBC_MAX);
  if (BE (preg->fastmap == NULL, 0))
    return REG_ESPACE;

  syntax |= (cflags & REG_ICASE) ? RE_ICASE : 0;


  if (cflags & REG_NEWLINE)
    {
      syntax &= ~RE_DOT_NEWLINE;
      syntax |= RE_HAT_LISTS_NOT_NEWLINE;

      preg->newline_anchor = 1;
    }
  else
    preg->newline_anchor = 0;
  preg->no_sub = !!(cflags & REG_NOSUB);
  preg->translate = NULL;

  ret = re_compile_internal (preg, pattern, strlen (pattern), syntax);


  if (ret == REG_ERPAREN)
    ret = REG_EPAREN;


  if (BE (ret == REG_NOERROR, 1))


    (void) re_compile_fastmap (preg);
  else
    {

      re_free (preg->fastmap);
      preg->fastmap = NULL;
    }

  return (int) ret;
}
