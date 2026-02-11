split_all_insns (void)
{
  sbitmap blocks;
  bool changed;
  basic_block bb;

  blocks = sbitmap_alloc (last_basic_block);
  bitmap_clear (blocks);
  changed = false;

  FOR_EACH_BB_REVERSE (bb)
    {
      rtx insn, next;
      bool finish = false;

      rtl_profile_for_bb (bb);
      for (insn = BB_HEAD (bb); !finish ; insn = next)
	{


	  next = NEXT_INSN (insn);
	  finish = (insn == BB_END (bb));
	  if (INSN_P (insn))
	    {
	      rtx set = single_set (insn);


	      if (set && set_noop_p (set))
		{


		  if (reload_completed)
		      delete_insn_and_edges (insn);
		}
	      else
		{
		  if (split_insn (insn))
		    {
		      bitmap_set_bit (blocks, bb->index);
		      changed = true;
		    }
		}
	    }
	}
    }

  default_rtl_profile ();
  if (changed)
    find_many_sub_basic_blocks (blocks);

#ifdef ENABLE_CHECKING
  verify_flow_info ();
#endif

  sbitmap_free (blocks);
}
