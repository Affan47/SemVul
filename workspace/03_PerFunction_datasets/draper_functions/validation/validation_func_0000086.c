math3d_lib_quatf_slerp(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj p_scm;
  ScmQuatf* p;
  ScmObj q_scm;
  ScmQuatf* q;
  ScmObj t_scm;
  double t;
  ScmObj SCM_SUBRARGS[3];
  int SCM_i;
  SCM_ENTER_SUBR("quatf-slerp");
  for (SCM_i=0; SCM_i<3; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  p_scm = SCM_SUBRARGS[0];
  if (!SCM_QUATFP(p_scm)) Scm_Error("<quatf> required, but got %S", p_scm);
  p = SCM_QUATF(p_scm);
  q_scm = SCM_SUBRARGS[1];
  if (!SCM_QUATFP(q_scm)) Scm_Error("<quatf> required, but got %S", q_scm);
  q = SCM_QUATF(q_scm);
  t_scm = SCM_SUBRARGS[2];
  if (!SCM_REALP(t_scm)) Scm_Error("real number required, but got %S", t_scm);
  t = Scm_GetDouble(t_scm);
  {
{
ScmObj SCM_RESULT;

#line 746 "math3d-lib.stub"
{float r[4];
Scm_QuatfSlerp(r,SCM_QUATF_D(p),SCM_QUATF_D(q),t);
SCM_RESULT=(Scm_MakeQuatfv(r));}
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
