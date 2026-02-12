re_compile_pattern (const char *pattern, size_t length,
		    struct re_pattern_buffer *bufp)
#endif
{
  reg_errcode_t ret;


  bufp->no_sub = !!(re_syntax_options & RE_NO_SUB);


  bufp->newline_anchor = 1;

  ret = re_compile_internal (bufp, pattern, length, re_syntax_options);

  if (!ret)
    return NULL;
  return gettext (__re_error_msgid + __re_error_msgid_idx[(int) ret]);
}
