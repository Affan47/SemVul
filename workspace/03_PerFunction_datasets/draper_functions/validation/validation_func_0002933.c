store_init_value (tree decl, tree init)
{
  tree value, type;


  type = TREE_TYPE (decl);
  if (TREE_CODE (type) == ERROR_MARK)
    return;


  value = digest_init (type, init, TREE_STATIC (decl));


  if (warn_traditional && !in_system_header
      && AGGREGATE_TYPE_P (TREE_TYPE (decl)) && ! TREE_STATIC (decl))
    warning ("traditional C rejects automatic aggregate initialization");

  DECL_INITIAL (decl) = value;


  STRIP_TYPE_NOPS (value);
  constant_expression_warning (value);


  if (TREE_CODE (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == 0
      && value != error_mark_node)
    {
      tree inside_init = init;

      if (TREE_CODE (init) == NON_LVALUE_EXPR)
	inside_init = TREE_OPERAND (init, 0);
      inside_init = fold (inside_init);

      if (TREE_CODE (inside_init) == COMPOUND_LITERAL_EXPR)
	{
	  tree decl = COMPOUND_LITERAL_EXPR_DECL (inside_init);

	  if (TYPE_DOMAIN (TREE_TYPE (decl)))
	    {


	      TYPE_DOMAIN (type) = TYPE_DOMAIN (TREE_TYPE (decl));
	      layout_type (type);
	      layout_decl (decl, 0);
	    }
	}
    }
}
