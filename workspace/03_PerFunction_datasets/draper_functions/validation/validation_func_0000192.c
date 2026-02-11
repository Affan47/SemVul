build_vec_delete_1 (tree base, tree maxindex, tree type,
    special_function_kind auto_delete_vec, int use_global_delete)
{
  tree virtual_size;
  tree ptype = build_pointer_type (type = complete_type (type));
  tree size_exp = size_in_bytes (type);


  tree tbase, tbase_init;


  tree body;


  tree loop = 0;


  tree deallocate_expr = 0;


  tree controller = NULL_TREE;


  if (TREE_CODE (type) == ARRAY_TYPE)
    abort ();

  if (! IS_AGGR_TYPE (type) || TYPE_HAS_TRIVIAL_DESTRUCTOR (type))
    goto no_destructor;


  virtual_size = size_binop (MULT_EXPR, size_exp,
			     convert (sizetype, maxindex));

  tbase = create_temporary_var (ptype);
  tbase_init = build_modify_expr (tbase, NOP_EXPR,
				  fold (build (PLUS_EXPR, ptype,
					       base,
					       virtual_size)));
  DECL_REGISTER (tbase) = 1;
  controller = build (BIND_EXPR, void_type_node, tbase, NULL_TREE, NULL_TREE);
  TREE_SIDE_EFFECTS (controller) = 1;

  body = build (EXIT_EXPR, void_type_node,
		build (EQ_EXPR, boolean_type_node, base, tbase));
  body = build_compound_expr
    (body, build_modify_expr (tbase, NOP_EXPR,
			      build (MINUS_EXPR, ptype, tbase, size_exp)));
  body = build_compound_expr
    (body, build_delete (ptype, tbase, sfk_complete_destructor,
			 LOOKUP_NORMAL|LOOKUP_DESTRUCTOR, 1));

  loop = build (LOOP_EXPR, void_type_node, body);
  loop = build_compound_expr (tbase_init, loop);

 no_destructor:


  if (auto_delete_vec != sfk_base_destructor)
    {
      tree base_tbd;


      virtual_size = size_binop (MULT_EXPR, size_exp,
				 convert (sizetype, maxindex));

      if (! TYPE_VEC_NEW_USES_COOKIE (type))

	base_tbd = base;
      else
	{
	  tree cookie_size;

	  cookie_size = get_cookie_size (type);
	  base_tbd
	    = cp_convert (ptype,
			  cp_build_binary_op (MINUS_EXPR,
					      cp_convert (string_type_node,
							  base),
					      cookie_size));

	  virtual_size = size_binop (PLUS_EXPR, virtual_size, cookie_size);
	}

      if (auto_delete_vec == sfk_deleting_destructor)
	deallocate_expr = build_x_delete (base_tbd,
					  2 | use_global_delete,
					  virtual_size);
    }

  body = loop;
  if (!deallocate_expr)
    ;
  else if (!body)
    body = deallocate_expr;
  else
    body = build_compound_expr (body, deallocate_expr);

  if (!body)
    body = integer_zero_node;


  body = fold (build (COND_EXPR, void_type_node,
		      fold (build (NE_EXPR, boolean_type_node, base,
				   integer_zero_node)),
		      body, integer_zero_node));
  body = build1 (NOP_EXPR, void_type_node, body);

  if (controller)
    {
      TREE_OPERAND (controller, 1) = body;
      body = controller;
    }

  if (TREE_CODE (base) == SAVE_EXPR)

    body = build (COMPOUND_EXPR, void_type_node, base, body);

  return convert_to_void (body, NULL);
}
