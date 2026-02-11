scm_markstream (SCM ptr)
{
  int openp;
  openp = SCM_CELL_WORD_0 (ptr) & SCM_OPN;
  if (openp)
    return SCM_PACK (SCM_STREAM (ptr));
  else
    return SCM_BOOL_F;
}
