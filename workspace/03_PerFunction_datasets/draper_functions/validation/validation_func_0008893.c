maybe_fold_tmr (tree ref)
{
  struct mem_address addr;
  bool changed = false;
  tree new_ref, off;

  get_address_description (ref, &addr);

  if (addr.base
      && TREE_CODE (addr.base) == INTEGER_CST
      && !integer_zerop (addr.base))
    {
      addr.offset = fold_binary_to_constant (PLUS_EXPR,
					     TREE_TYPE (addr.offset),
					     addr.offset, addr.base);
      addr.base = NULL_TREE;
      changed = true;
    }

  if (addr.symbol
      && TREE_CODE (TREE_OPERAND (addr.symbol, 0)) == MEM_REF)
    {
      addr.offset = fold_binary_to_constant
			(PLUS_EXPR, TREE_TYPE (addr.offset),
			 addr.offset,
			 TREE_OPERAND (TREE_OPERAND (addr.symbol, 0), 1));
      addr.symbol = TREE_OPERAND (TREE_OPERAND (addr.symbol, 0), 0);
      changed = true;
    }
  else if (addr.symbol
	   && handled_component_p (TREE_OPERAND (addr.symbol, 0)))
    {
      HOST_WIDE_INT offset;
      addr.symbol = build_fold_addr_expr
		      (get_addr_base_and_unit_offset
		         (TREE_OPERAND (addr.symbol, 0), &offset));
      addr.offset = int_const_binop (PLUS_EXPR,
				     addr.offset, size_int (offset));
      changed = true;
    }

  if (addr.index && TREE_CODE (addr.index) == INTEGER_CST)
    {
      off = addr.index;
      if (addr.step)
	{
	  off = fold_binary_to_constant (MULT_EXPR, sizetype,
					 off, addr.step);
	  addr.step = NULL_TREE;
	}

      addr.offset = fold_binary_to_constant (PLUS_EXPR,
					     TREE_TYPE (addr.offset),
					     addr.offset, off);
      addr.index = NULL_TREE;
      changed = true;
    }

  if (!changed)
    return NULL_TREE;


  new_ref = create_mem_ref_raw (TREE_TYPE (ref),
			        TREE_TYPE (addr.offset), &addr, false);
  TREE_SIDE_EFFECTS (new_ref) = TREE_SIDE_EFFECTS (ref);
  TREE_THIS_VOLATILE (new_ref) = TREE_THIS_VOLATILE (ref);
  return new_ref;
}
