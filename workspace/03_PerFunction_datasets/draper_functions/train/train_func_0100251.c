libevalinteraction_environment(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj SCM_SUBRARGS[0];
  int SCM_i;
  SCM_ENTER_SUBR("interaction-environment");
  for (SCM_i=0; SCM_i<0; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  {
{
ScmObj SCM_RESULT;

#line 59 "libeval.scm"
SCM_RESULT=(SCM_OBJ(Scm_UserModule()));
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
