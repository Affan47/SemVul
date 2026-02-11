compute_object_sizes (void)
{
  basic_block bb;
  FOR_EACH_BB (bb)
    {
      gimple_stmt_iterator i;
      for (i = gsi_start_bb (bb); !gsi_end_p (i); gsi_next (&i))
	{
	  tree callee, result;
	  gimple call = gsi_stmt (i);

          if (gimple_code (call) != GIMPLE_CALL)
	    continue;

	  callee = gimple_call_fndecl (call);
	  if (!callee
	      || DECL_BUILT_IN_CLASS (callee) != BUILT_IN_NORMAL
	      || DECL_FUNCTION_CODE (callee) != BUILT_IN_OBJECT_SIZE)
	    continue;

	  init_object_sizes ();
	  result = fold_call_stmt (call, false);
	  if (!result)
	    {
	      if (gimple_call_num_args (call) == 2
		  && POINTER_TYPE_P (TREE_TYPE (gimple_call_arg (call, 0))))
		{
		  tree ost = gimple_call_arg (call, 1);

		  if (host_integerp (ost, 1))
		    {
		      unsigned HOST_WIDE_INT object_size_type
			= tree_low_cst (ost, 1);

		      if (object_size_type < 2)
			result = fold_convert (size_type_node,
					       integer_minus_one_node);
		      else if (object_size_type < 4)
			result = build_zero_cst (size_type_node);
		    }
		}

	      if (!result)
		continue;
	    }

	  if (dump_file && (dump_flags & TDF_DETAILS))
	    {
	      fprintf (dump_file, "Simplified\n  ");
	      print_gimple_stmt (dump_file, call, 0, dump_flags);
	    }

	  if (!update_call_from_tree (&i, result))
	    gcc_unreachable ();

	  if (dump_file && (dump_flags & TDF_DETAILS))
	    {
	      fprintf (dump_file, "to\n  ");
	      print_gimple_stmt (dump_file, gsi_stmt (i), 0, dump_flags);
	      fprintf (dump_file, "\n");
	    }
	}
    }

  fini_object_sizes ();
  return 0;
}
