compute_dominance_frontiers_1 (bitmap_head *frontiers)
{
  edge p;
  edge_iterator ei;
  basic_block b;
  FOR_EACH_BB (b)
    {
      if (EDGE_COUNT (b->preds) >= 2)
	{
	  FOR_EACH_EDGE (p, ei, b->preds)
	    {
	      basic_block runner = p->src;
	      basic_block domsb;
	      if (runner == ENTRY_BLOCK_PTR)
		continue;

	      domsb = get_immediate_dominator (CDI_DOMINATORS, b);
	      while (runner != domsb)
		{
		  if (!bitmap_set_bit (&frontiers[runner->index],
				       b->index))
		    break;
		  runner = get_immediate_dominator (CDI_DOMINATORS,
						    runner);
		}
	    }
	}
    }
}
