genericize_omp_for_stmt (tree *stmt_p, int *walk_subtrees, void *data)
{
  tree stmt = *stmt_p;
  location_t locus = EXPR_LOCATION (stmt);
  tree clab = begin_bc_block (bc_continue, locus);

  cp_walk_tree (&OMP_FOR_BODY (stmt), cp_genericize_r, data, NULL);
  cp_walk_tree (&OMP_FOR_CLAUSES (stmt), cp_genericize_r, data, NULL);
  cp_walk_tree (&OMP_FOR_INIT (stmt), cp_genericize_r, data, NULL);
  cp_walk_tree (&OMP_FOR_COND (stmt), cp_genericize_r, data, NULL);
  cp_walk_tree (&OMP_FOR_INCR (stmt), cp_genericize_r, data, NULL);
  cp_walk_tree (&OMP_FOR_PRE_BODY (stmt), cp_genericize_r, data, NULL);
  *walk_subtrees = 0;

  finish_bc_block (&OMP_FOR_BODY (stmt), bc_continue, clab);
}
