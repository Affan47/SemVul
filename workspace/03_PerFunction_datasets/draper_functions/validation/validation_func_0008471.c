gimple_init_edge_profiler (void)
{
  tree interval_profiler_fn_type;
  tree pow2_profiler_fn_type;
  tree one_value_profiler_fn_type;
  tree gcov_type_ptr;
  tree ic_profiler_fn_type;
  tree average_profiler_fn_type;

  if (!gcov_type_node)
    {
      gcov_type_node = get_gcov_type ();
      gcov_type_ptr = build_pointer_type (gcov_type_node);


      interval_profiler_fn_type
	      = build_function_type_list (void_type_node,
					  gcov_type_ptr, gcov_type_node,
					  integer_type_node,
					  unsigned_type_node, NULL_TREE);
      tree_interval_profiler_fn
	      = build_fn_decl ("__gcov_interval_profiler",
				     interval_profiler_fn_type);
      TREE_NOTHROW (tree_interval_profiler_fn) = 1;
      DECL_ATTRIBUTES (tree_interval_profiler_fn)
	= tree_cons (get_identifier ("leaf"), NULL,
		     DECL_ATTRIBUTES (tree_interval_profiler_fn));


      pow2_profiler_fn_type
	      = build_function_type_list (void_type_node,
					  gcov_type_ptr, gcov_type_node,
					  NULL_TREE);
      tree_pow2_profiler_fn = build_fn_decl ("__gcov_pow2_profiler",
						   pow2_profiler_fn_type);
      TREE_NOTHROW (tree_pow2_profiler_fn) = 1;
      DECL_ATTRIBUTES (tree_pow2_profiler_fn)
	= tree_cons (get_identifier ("leaf"), NULL,
		     DECL_ATTRIBUTES (tree_pow2_profiler_fn));


      one_value_profiler_fn_type
	      = build_function_type_list (void_type_node,
					  gcov_type_ptr, gcov_type_node,
					  NULL_TREE);
      tree_one_value_profiler_fn
	      = build_fn_decl ("__gcov_one_value_profiler",
				     one_value_profiler_fn_type);
      TREE_NOTHROW (tree_one_value_profiler_fn) = 1;
      DECL_ATTRIBUTES (tree_one_value_profiler_fn)
	= tree_cons (get_identifier ("leaf"), NULL,
		     DECL_ATTRIBUTES (tree_one_value_profiler_fn));

      init_ic_make_global_vars ();


      ic_profiler_fn_type
	       = build_function_type_list (void_type_node,
					  gcov_type_ptr, gcov_type_node,
					  ptr_void,
					  ptr_void, NULL_TREE);
      tree_indirect_call_profiler_fn
	      = build_fn_decl ("__gcov_indirect_call_profiler",
				     ic_profiler_fn_type);
      TREE_NOTHROW (tree_indirect_call_profiler_fn) = 1;
      DECL_ATTRIBUTES (tree_indirect_call_profiler_fn)
	= tree_cons (get_identifier ("leaf"), NULL,
		     DECL_ATTRIBUTES (tree_indirect_call_profiler_fn));


      average_profiler_fn_type
	      = build_function_type_list (void_type_node,
					  gcov_type_ptr, gcov_type_node, NULL_TREE);
      tree_average_profiler_fn
	      = build_fn_decl ("__gcov_average_profiler",
				     average_profiler_fn_type);
      TREE_NOTHROW (tree_average_profiler_fn) = 1;
      DECL_ATTRIBUTES (tree_average_profiler_fn)
	= tree_cons (get_identifier ("leaf"), NULL,
		     DECL_ATTRIBUTES (tree_average_profiler_fn));
      tree_ior_profiler_fn
	      = build_fn_decl ("__gcov_ior_profiler",
				     average_profiler_fn_type);
      TREE_NOTHROW (tree_ior_profiler_fn) = 1;
      DECL_ATTRIBUTES (tree_ior_profiler_fn)
	= tree_cons (get_identifier ("leaf"), NULL,
		     DECL_ATTRIBUTES (tree_ior_profiler_fn));


      DECL_ASSEMBLER_NAME (tree_interval_profiler_fn);
      DECL_ASSEMBLER_NAME (tree_pow2_profiler_fn);
      DECL_ASSEMBLER_NAME (tree_one_value_profiler_fn);
      DECL_ASSEMBLER_NAME (tree_indirect_call_profiler_fn);
      DECL_ASSEMBLER_NAME (tree_average_profiler_fn);
      DECL_ASSEMBLER_NAME (tree_ior_profiler_fn);
    }
}
