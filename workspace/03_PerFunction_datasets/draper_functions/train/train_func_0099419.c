move_pointer_to_base (struct mem_address *parts, aff_tree *addr)
{
  unsigned i;
  tree val = NULL_TREE;

  for (i = 0; i < addr->n; i++)
    {
      if (!addr->elts[i].coef.is_one ())
	continue;

      val = addr->elts[i].val;
      if (POINTER_TYPE_P (TREE_TYPE (val)))
	break;
    }

  if (i == addr->n)
    return;

  parts->base = val;
  aff_combination_remove_elt (addr, i);
}
