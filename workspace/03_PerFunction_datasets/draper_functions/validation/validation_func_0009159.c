end_java_method (void)
{
  tree fndecl = current_function_decl;


  poplevel (1, 1, 0);


  poplevel (1, 0, 1);

  BLOCK_SUPERCONTEXT (DECL_INITIAL (fndecl)) = fndecl;

  if (DECL_SAVED_TREE (fndecl))
    {
      tree fbody, block_body;


      fbody = DECL_SAVED_TREE (fndecl);
      block_body = BIND_EXPR_BODY (fbody);
      htab_traverse (DECL_FUNCTION_INIT_TEST_TABLE (fndecl),
		     attach_init_test_initialization_flags, block_body);
    }

  finish_method (fndecl);

  current_function_decl = NULL_TREE;
  base_decl_map = NULL_TREE;
}
