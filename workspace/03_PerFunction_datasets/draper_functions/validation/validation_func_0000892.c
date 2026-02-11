store_can_be_removed_p (ira_allocno_t src_allocno, ira_allocno_t dest_allocno)
{
  int regno, orig_regno;
  ira_allocno_t a;
  ira_loop_tree_node_t node;

  ira_assert (ALLOCNO_CAP_MEMBER (src_allocno) == NULL
	      && ALLOCNO_CAP_MEMBER (dest_allocno) == NULL);
  orig_regno = ALLOCNO_REGNO (src_allocno);
  regno = REGNO (allocno_emit_reg (dest_allocno));
  for (node = ALLOCNO_LOOP_TREE_NODE (src_allocno);
       node != NULL;
       node = node->parent)
    {
      a = node->regno_allocno_map[orig_regno];
      ira_assert (a != NULL);
      if (REGNO (allocno_emit_reg (a)) == (unsigned) regno)

	return true;
      else if (bitmap_bit_p (node->modified_regnos, orig_regno))
	return false;
      else if (node->entered_from_non_parent_p)


	return false;
    }

  return false;
}
