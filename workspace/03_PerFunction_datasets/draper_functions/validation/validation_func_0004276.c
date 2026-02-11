genericize_for_stmt (tree *stmt_p, int *walk_subtrees, void *data)
{
  tree stmt = *stmt_p;
  tree expr = NULL;
  tree loop;
  tree init = FOR_INIT_STMT (stmt);

  if (init)
    {
      cp_walk_tree (&init, cp_genericize_r, data, NULL);
      append_to_statement_list (init, &expr);
    }

  genericize_cp_loop (&loop, EXPR_LOCATION (stmt), FOR_COND (stmt),
		      FOR_BODY (stmt), FOR_EXPR (stmt), 1, walk_subtrees, data);
  append_to_statement_list (loop, &expr);
  *stmt_p = expr;
}
