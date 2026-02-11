libevalvm_set_default_exception_handler(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj vm_scm;
  ScmVM* vm;
  ScmObj handler_scm;
  ScmObj handler;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("vm-set-default-exception-handler");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  vm_scm = SCM_SUBRARGS[0];
  if (!SCM_VMP(vm_scm)) Scm_Error("thread required, but got %S", vm_scm);
  vm = SCM_VM(vm_scm);
  handler_scm = SCM_SUBRARGS[1];
  handler = (handler_scm);
  {

#line 404 "libeval.scm"
if (!((SCM_FALSEP(handler))||(SCM_PROCEDUREP(handler)))){{
SCM_TYPE_ERROR(handler,"a procedure or #f");}}

#line 406 "libeval.scm"
(vm)->defaultEscapeHandler=(handler);
SCM_RETURN(SCM_UNDEFINED);
  }
}
