gimplify_decl_expr (tree *stmt_p, gimple_seq *seq_p)
{
  tree stmt = *stmt_p;
  tree decl = DECL_EXPR_DECL (stmt);

  *stmt_p = NULL_TREE;

  if (TREE_TYPE (decl) == error_mark_node)
    return GS_ERROR;

  if ((TREE_CODE (decl) == TYPE_DECL
       || TREE_CODE (decl) == VAR_DECL)
      && !TYPE_SIZES_GIMPLIFIED (TREE_TYPE (decl)))
    gimplify_type_sizes (TREE_TYPE (decl), seq_p);

  if (TREE_CODE (decl) == VAR_DECL && !DECL_EXTERNAL (decl))
    {
      tree init = DECL_INITIAL (decl);

      if (TREE_CODE (DECL_SIZE_UNIT (decl)) != INTEGER_CST
	  || (!TREE_STATIC (decl)
	      && flag_stack_check == GENERIC_STACK_CHECK
	      && compare_tree_int (DECL_SIZE_UNIT (decl),
				   STACK_CHECK_MAX_VAR_SIZE) > 0))
	gimplify_vla_decl (decl, seq_p);


      if (!DECL_SEEN_IN_BIND_EXPR_P (decl)
	  && DECL_ARTIFICIAL (decl) && DECL_NAME (decl) == NULL_TREE)
	gimple_add_tmp_var (decl);

      if (init && init != error_mark_node)
	{
	  if (!TREE_STATIC (decl))
	    {
	      DECL_INITIAL (decl) = NULL_TREE;
	      init = build2 (INIT_EXPR, void_type_node, decl, init);
	      gimplify_and_add (init, seq_p);
	      ggc_free (init);
	    }
	  else


	    walk_tree (&init, force_labels_r, NULL, NULL);
	}
    }

  return GS_ALL_DONE;
}
