pango_break_pango_find_paragraph_boundary(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj text_scm;
  ScmString* text;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("pango-find-paragraph-boundary");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  text_scm = SCM_SUBRARGS[0];
  if (!SCM_STRINGP(text_scm)) Scm_Error("string required, but got %S", text_scm);
  text = SCM_STRING(text_scm);
  {
const gchar *s = Scm_GetStringConst(text);
  int len = SCM_STRING_SIZE(text); gint index, start;
  pango_find_paragraph_boundary(s, len, &index, &start);
  SCM_RETURN2(Scm_MakeInteger(index), Scm_MakeInteger(start));
  }
}
