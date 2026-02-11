libsyssys_crypt(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj key_scm;
  const char * key;
  ScmObj salt_scm;
  const char * salt;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("sys-crypt");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  key_scm = SCM_SUBRARGS[0];
  if (!SCM_STRINGP(key_scm)) Scm_Error("const C string required, but got %S", key_scm);
  key = SCM_STRING_CONST_CSTRING(key_scm);
  salt_scm = SCM_SUBRARGS[1];
  if (!SCM_STRINGP(salt_scm)) Scm_Error("const C string required, but got %S", salt_scm);
  salt = SCM_STRING_CONST_CSTRING(salt_scm);
  {
{
const char * SCM_RESULT;

#line 1113 "libsys.scm"
SCM_RESULT=(((const char * )(crypt(key,salt))));
SCM_RETURN(SCM_MAKE_STR_COPYING(SCM_RESULT));
}
  }
}
