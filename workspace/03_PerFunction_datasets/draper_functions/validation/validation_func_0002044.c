util__sparsesparse_table_num_entries(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj st_scm;
  SparseTable* st;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("sparse-table-num-entries");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  st_scm = SCM_SUBRARGS[0];
  if (!SPARSE_TABLE_P(st_scm)) Scm_Error("sparse table required, but got %S", st_scm);
  st = SPARSE_TABLE(st_scm);
  {
{
u_long SCM_RESULT;

#line 137 "./sparse.scm"
SCM_RESULT=((st)->numEntries);
SCM_RETURN(Scm_MakeIntegerFromUI(SCM_RESULT));
}
  }
}
