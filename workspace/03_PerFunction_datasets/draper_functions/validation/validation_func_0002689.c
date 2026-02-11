re_compile_pattern (pattern, length, bufp)
     const char *pattern;
     size_t length;
     struct re_pattern_buffer *bufp;
{
  reg_errcode_t ret;


  bufp->regs_allocated = REGS_UNALLOCATED;


  bufp->no_sub = 0;


  bufp->newline_anchor = 1;

  ret = regex_compile (pattern, length, re_syntax_options, bufp);

  if (!ret)
    return NULL;
  return gettext (re_error_msgid + re_error_msgid_idx[(int) ret]);
}
