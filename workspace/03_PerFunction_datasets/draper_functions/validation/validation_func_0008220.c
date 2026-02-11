c_expand_asm_operands (tree string, tree outputs, tree inputs,
		       tree clobbers, int vol, location_t locus)
{
  int noutputs = list_length (outputs);
  int i;

  tree *o = alloca (noutputs * sizeof (tree));
  tree tail;


  for (i = 0, tail = outputs; tail; tail = TREE_CHAIN (tail), i++)
    {
      o[i] = TREE_VALUE (tail);
      if (o[i] == error_mark_node)
	return;
    }


  expand_asm_operands (string, outputs, inputs, clobbers, vol, locus);


  for (i = 0, tail = outputs; tail; tail = TREE_CHAIN (tail), i++)
    {
      if (o[i] != TREE_VALUE (tail))
	{
	  expand_expr (build_modify_expr (o[i], NOP_EXPR, TREE_VALUE (tail)),
		       NULL_RTX, VOIDmode, EXPAND_NORMAL);
	  free_temp_slots ();


	  TREE_VALUE (tail) = o[i];
	}


      else
	{
	  tree type = TREE_TYPE (o[i]);
	  if (TREE_READONLY (o[i])
	      || TYPE_READONLY (type)
	      || ((TREE_CODE (type) == RECORD_TYPE
		   || TREE_CODE (type) == UNION_TYPE)
		  && C_TYPE_FIELDS_READONLY (type)))
	    readonly_error (o[i], "modification by `asm'");
	}
    }


  emit_queue ();
}
