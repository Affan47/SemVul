libsyssys_sigset_addX(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj set_scm;
  ScmSysSigset* set;
  ScmObj sigs_scm;
  ScmObj sigs;
  ScmObj SCM_SUBRARGS[3];
  int SCM_i;
  SCM_ENTER_SUBR("sys-sigset-add!");
  for (SCM_i=0; SCM_i<3; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  set_scm = SCM_SUBRARGS[0];
  if (!SCM_SYS_SIGSET_P(set_scm)) Scm_Error("<sys-sigset> required, but got %S", set_scm);
  set = SCM_SYS_SIGSET(set_scm);
  sigs_scm = SCM_SUBRARGS[SCM_ARGCNT-1];
  sigs = (sigs_scm);
  {
{
ScmObj SCM_RESULT;

#line 329 "libsys.scm"
SCM_RESULT=(Scm_SysSigsetOp(set,sigs,FALSE));
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
