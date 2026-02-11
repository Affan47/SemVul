analyze_matrix_allocation_site (struct matrix_info *mi, gimple stmt,
				int level, sbitmap visited)
{
  if (gimple_assign_copy_p (stmt) || gimple_assign_cast_p (stmt))
    {
      tree rhs = gimple_assign_rhs1 (stmt);

      if (TREE_CODE (rhs) == SSA_NAME)
	{
	  gimple def = SSA_NAME_DEF_STMT (rhs);

	  analyze_matrix_allocation_site (mi, def, level, visited);
	  return;
	}


      else if (rhs == mi->decl)
	return;
    }

  else if (is_gimple_call (stmt))
    {
      int call_flags = gimple_call_flags (stmt);

      if (!(call_flags & ECF_MALLOC))
	{
	  mark_min_matrix_escape_level (mi, level, stmt);
	  return;
	}
      else
	{
	  tree malloc_fn_decl;

	  malloc_fn_decl = gimple_call_fndecl (stmt);
	  if (malloc_fn_decl == NULL_TREE)
	    {
	      mark_min_matrix_escape_level (mi, level, stmt);
	      return;
	    }
	  if (DECL_FUNCTION_CODE (malloc_fn_decl) != BUILT_IN_MALLOC)
	    {
	      if (dump_file)
		fprintf (dump_file,
			 "Matrix %s is an argument to function %s\n",
			 get_name (mi->decl), get_name (malloc_fn_decl));
	      mark_min_matrix_escape_level (mi, level, stmt);
	      return;
	    }
	}


      if (mi->malloc_for_level
	  && mi->max_malloced_level-1 == level
	  && mi->malloc_for_level[level] != stmt)
	{
	  mark_min_matrix_escape_level (mi, level, stmt);
	  return;
	}
      else
	add_allocation_site (mi, stmt, level);
      return;
    }


  mark_min_matrix_escape_level (mi, level, stmt);
}
