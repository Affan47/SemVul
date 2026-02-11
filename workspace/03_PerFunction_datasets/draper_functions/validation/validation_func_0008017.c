gtktreestore_gtk_tree_store_insert(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj store_scm;
  GtkTreeStore* store;
  ScmObj parent_scm;
  GtkTreeIter* parent;
  ScmObj position_scm;
  int position;
  ScmObj SCM_SUBRARGS[3];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-tree-store-insert");
  for (SCM_i=0; SCM_i<3; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  store_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_TREE_STORE_P(store_scm)) Scm_Error("<gtk-tree-store> required, but got %S", store_scm);
  store = SCM_GTK_TREE_STORE(store_scm);
  parent_scm = SCM_SUBRARGS[1];
  if (!SCM_GTK_TREE_ITER_OR_NULL_P(parent_scm)) Scm_Error("<gtk-tree-iter>-or-null required, but got %S", parent_scm);
  parent = SCM_GTK_TREE_ITER(parent_scm);
  position_scm = SCM_SUBRARGS[2];
  if (!SCM_INTEGERP(position_scm)) Scm_Error("C integer required, but got %S", position_scm);
  position = Scm_GetInteger(position_scm);
  {
GtkTreeIter iter;
  gtk_tree_store_insert(store, &iter, parent, position);
  SCM_RETURN(SCM_MAKE_GTK_TREE_ITER(&iter));
  }
}
